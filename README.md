


Rule Engine with Abstract Syntax Tree (AST)

Overview
This project implements a rule engine using an Abstract Syntax Tree (AST) to evaluate user eligibility based on attributes like age, department, salary, and experience.

Features
AST Representation: Create rules and represent them as an AST.
Rule Combination: Combine rules dynamically using logical operators (AND, OR).
Evaluation: Evaluate the rules against user-provided data.

Setup
Clone the repository:

git clone <your-repository-url>
cd rule-engine

Compile the code:

g++ -std=c++11 main.cpp -o rule_engine

Run the executable:

./rule_engine
Usage
create_rule(rule_string): Create an AST from a rule string.
combine_rules(rule1, rule2):Combine two rules using AND.
evaluate_rule(ast, data): Evaluate the rule against data.

Example
auto rule1 = create_rule("rule1");
auto combined_rule = combine_rules(rule1, rule2);
std::map<std::string, int> data = {{"age", 35}, {"department", 1}};
bool result = evaluate_rule(combined_rule, data);

Sample Output:
Data matches combined rule: True

Author
NANDINI TANDON
Nandini23.nt@gmail.com
