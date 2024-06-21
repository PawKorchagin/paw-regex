#pragma once

#include <type_traits>
#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <stack>
#include <set>

// #define debug(x) std::cerr << (#x) << " = " << x << "\n"

namespace pgx {
template<typename T>
concept StringLike = std::is_convertible_v<T, std::string_view>;

class CRegex {
public:
    template<StringLike S>
    CRegex(const S& s) 
    : pattern_(ConvertToPostfix(s))
    , automata_(ConvertToENFA(pattern_)) {
        for (auto& c : pattern_) {
            if (c != '*' && c != '|') {
                alph_.insert(c);
            }
        }
    }

    template<StringLike S>
    bool IsMatch(S s) const {
        for (auto c : s) if (!alph_.contains(c)) return false;
        return MatchENFA(automata_.start_, s, 0);
    }

    void PrintAutomata() {
        std::set<int> vis;
        printENFA(automata_.start_, vis);
    }

private:
    class State {
    public:
        int id_;
        bool is_final_;
        std::vector<std::pair<char, State*>> transitions_;
        std::vector<State*> eps_transitions_;

        State(int id, bool is_final_ = false) : id_(id), is_final_(is_final_) {}
    };

    class ENFA {
    public:
        State* start_;
        State* final_;

        ENFA(State* start, State* final) 
            : start_(start), final_(final) {}

        static ENFA literal(char c, int &cnt) {
            State* start = new State(cnt++);
            State* end = new State(cnt++, true);
            start->transitions_.push_back({c, end});
            return ENFA(start, end);
        }

        static ENFA concatenate(ENFA enfa1, ENFA enfa2) {
            enfa1.final_->is_final_ = false;
            enfa1.final_->eps_transitions_.push_back(enfa2.start_);
            return ENFA(enfa1.start_, enfa2.final_);
        }

        static ENFA unionENFA(ENFA enfa1, ENFA enfa2, int &cnt) {
            State* start = new State(cnt++);
            State* end = new State(cnt++, true);
            start->eps_transitions_.push_back(enfa1.start_);
            start->eps_transitions_.push_back(enfa2.start_);
            enfa1.final_->is_final_ = false;
            enfa2.final_->is_final_ = false;
            enfa1.final_->eps_transitions_.push_back(end);
            enfa2.final_->eps_transitions_.push_back(end);
            return ENFA(start, end);
        }

        static ENFA kleeneStar(ENFA enfa, int &cnt) {
            State* start = new State(cnt++);
            State* end = new State(cnt++, true);
            start->eps_transitions_.push_back(enfa.start_);
            start->eps_transitions_.push_back(end);
            enfa.final_->is_final_ = false;
            enfa.final_->eps_transitions_.push_back(end);
            enfa.final_->eps_transitions_.push_back(enfa.start_);
            return ENFA(start, end);
        }
    };

    ENFA ConvertToENFA(const std::string_view pattern) {
        std::stack<ENFA> stack;
        int cnt = 0;

        for (char c : pattern) {
            // debug(c);
            if (c == '|') {
                ENFA enfa2 = stack.top(); stack.pop();
                ENFA enfa1 = stack.top(); stack.pop();
                stack.push(ENFA::unionENFA(enfa1, enfa2, cnt));
            } else if (c == '*') {
                ENFA enfa = stack.top(); stack.pop();
                stack.push(ENFA::kleeneStar(enfa, cnt));
            } else if (c == '.') {
                ENFA enfa2 = stack.top(); stack.pop();
                ENFA enfa1 = stack.top(); stack.pop();
                stack.push(ENFA::concatenate(enfa1, enfa2));
            } else {
                stack.push(ENFA::literal(c, cnt));
            }
        }

        while (stack.size() > 1) {
            auto enfa2 = stack.top(); stack.pop();
            auto enfa1 = stack.top(); stack.pop();
            stack.push(ENFA::concatenate(enfa1, enfa2));
        }

        State* start = new State(cnt++);
        State* end = stack.top().final_;
        start->eps_transitions_.push_back(stack.top().start_);

        return ENFA(start, end);
    }

    std::string ConvertToPostfix(std::string_view s) {

        std::string postfix;
        std::stack<char> stack;
        std::set<char> operators = {'|', '.', '*'};

        std::set<char> spec = {'|', '.', '*', '(', ')'};
        
        std::string pattern = "";
        for (int i = 0; i < static_cast<int>(s.size()) - 1; ++i) {
            pattern += s[i];
            if (!spec.contains(s[i]) && !spec.contains(s[i + 1])) {
                pattern += '.';
            }
        }

        pattern += s.back();
        // debug(pattern);

        // bool in_row = false;

        for (char c : pattern) {
            if (c == '(') {
                stack.push(c);
            } else if (c == ')') {
                while (!stack.empty() && stack.top() != '(') {
                    postfix += stack.top();
                    stack.pop();
                }
                stack.pop(); // Remove '('
            } else if (operators.find(c) != operators.end()) {
                while (!stack.empty() && stack.top() != '(' 
                    && (c == '|' ? stack.top() != '|' : c != '*')) {
                    postfix += stack.top();
                    stack.pop();
                }
                stack.push(c);
            } else {
                postfix += c;
            }
        }

        while (!stack.empty()) {
            postfix += stack.top();
            stack.pop();
        }

        return postfix;
    }

    void printENFA(State* state, std::set<int> &visited) {
        if (visited.find(state->id_) != visited.end()) return;
        visited.insert(state->id_);
        std::cout << "State " << state->id_ << (state->is_final_ ? " [Final]" : "") << ":\n";
        for (auto &trans : state->transitions_) {
            std::cout << "  -- " << trans.first << " --> State " << trans.second->id_ << "\n";
            // printENFA(trans.second, visited);
        }
        for (auto &eps : state->eps_transitions_) {
            std::cout << "  -- ε --> State " << eps->id_ << "\n";
            // printENFA(eps, visited);
        }
        for (auto &trans : state->transitions_) {
            // std::cout << "  -- " << trans.first << " --> State " << trans.second->id_ << "\n";
            printENFA(trans.second, visited);
        }
        for (auto &eps : state->eps_transitions_) {
            // std::cout << "  -- ε --> State " << eps->id_ << "\n";
            printENFA(eps, visited);
        }
    }

    bool MatchENFA(State* state, std::string_view request, int ind = 0) const {
        bool res = false;

        for (auto &[c, trans] : state->transitions_) {
            if (request[ind] == c)
                res |= MatchENFA(trans, request, ind + 1);
        }
        for (auto &eps : state->eps_transitions_) {
            res |= MatchENFA(eps, request, ind);
        }

        return res || (state->is_final_ && ind == request.size());
    }

    std::string pattern_;
    ENFA automata_;
    std::set<char> alph_;
};

template<StringLike... Args>
bool RegexMatch(CRegex&&, Args&&...);

template<typename Pred, StringLike... Args>
bool RegexMatch(Pred, CRegex&&, Args&&...);

template<StringLike Arg>
bool RegexMatch(CRegex&& pattern, Arg&& arg) {
    return pattern.IsMatch(std::forward<Arg>(arg));
}

template<typename Pred, StringLike Arg>
bool RegexMatch(Pred, CRegex&& pattern, Arg&& arg) {
    return pattern.IsMatch(std::forward<Arg>(arg));
}

struct pred_any {
    bool operator()(bool a, bool b) {
        return a || b;
    }
};

struct pred_all {
    bool operator()(bool a, bool b) {
        return a && b;
    }
};

pred_any any_case;
pred_all all_cases;

template<StringLike First, StringLike... Args>
bool RegexMatch(CRegex&& pattern, First&& first, Args&&... args) {
    return pattern.IsMatch(std::forward<First>(first)) 
        && RegexMatch(std::forward<CRegex>(pattern), std::forward<Args>(args)...);
}

template<typename Pred, StringLike First, StringLike... Args>
bool RegexMatch(Pred pred, CRegex&& pattern, First&& first, Args&&... args) {
    return pred(pattern.IsMatch(std::forward<First>(first)) 
        , RegexMatch(pred, std::forward<CRegex>(pattern), std::forward<Args>(args)...));
}
};