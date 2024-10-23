#include <iostream>
#include <map>
#include <string>
#include <memory>

// Node structure to represent rule components
struct Node {
    std::string value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(std::string val) : value(val), left(nullptr), right(nullptr) {}
};

// Function to evaluate the rule against data
bool evaluate_rule(const std::shared_ptr<Node>& node, const std::map<std::string, int>& data) {
    if (!node) return false;

    // Check for operators
    if (node->value == "AND") {
        return evaluate_rule(node->left, data) && evaluate_rule(node->right, data);
    } else if (node->value == "OR") {
        return evaluate_rule(node->left, data) || evaluate_rule(node->right, data);
    }

    // Extract comparison key and value from node value
    size_t pos = node->value.find('>');
    if (pos != std::string::npos) {
        std::string key = node->value.substr(0, pos);
        int threshold = std::stoi(node->value.substr(pos + 1));
        return data.at(key) > threshold;
    }

    pos = node->value.find('<');
    if (pos != std::string::npos) {
        std::string key = node->value.substr(0, pos);
        int threshold = std::stoi(node->value.substr(pos + 1));
        return data.at(key) < threshold;
    }

    pos = node->value.find("==");
    if (pos != std::string::npos) {
        std::string key = node->value.substr(0, pos);
        int threshold = std::stoi(node->value.substr(pos + 2));
        return data.at(key) == threshold;
    }

    // If none of the conditions match, return false
    return false;
}

// Function to combine two rules using AND
std::shared_ptr<Node> combine_rules(const std::shared_ptr<Node>& rule1, const std::shared_ptr<Node>& rule2) {
    auto combined = std::make_shared<Node>("AND");
    combined->left = rule1;
    combined->right = rule2;
    return combined;
}

// Function to create predefined rules
std::shared_ptr<Node> create_rule(const std::string& rule_name) {
    if (rule_name == "rule1") {
        auto node1 = std::make_shared<Node>("age>30");
        auto node2 = std::make_shared<Node>("department==1");
        auto andNode1 = std::make_shared<Node>("AND");
        andNode1->left = node1;
        andNode1->right = node2;

        auto node3 = std::make_shared<Node>("salary>50000");
        auto node4 = std::make_shared<Node>("experience>5");
        auto orNode1 = std::make_shared<Node>("OR");
        orNode1->left = node3;
        orNode1->right = node4;

        auto andNode2 = std::make_shared<Node>("AND");
        andNode2->left = andNode1;
        andNode2->right = orNode1;

        return andNode2; // Full rule1
    } else if (rule_name == "rule2") {
        auto node1 = std::make_shared<Node>("age>30");
        auto node2 = std::make_shared<Node>("department==2");
        auto andNode1 = std::make_shared<Node>("AND");
        andNode1->left = node1;
        andNode1->right = node2;

        auto node3 = std::make_shared<Node>("salary>20000");
        auto node4 = std::make_shared<Node>("experience>5");
        auto orNode1 = std::make_shared<Node>("OR");
        orNode1->left = node3;
        orNode1->right = node4;

        auto andNode2 = std::make_shared<Node>("AND");
        andNode2->left = andNode1;
        andNode2->right = orNode1;

        return andNode2; // Full rule2
    }
    return nullptr;
}

int main() {
    try {
        // Create individual rules
        auto rule1 = create_rule("rule1");
        auto rule2 = create_rule("rule2");

        // Combine rules
        auto combined_rule = combine_rules(rule1, rule2);

        // Example data for evaluation
        std::map<std::string, int> data1 = {{"age", 35}, {"department", 1}, {"salary", 60000}, {"experience", 3}};
        std::map<std::string, int> data2 = {{"age", 22}, {"department", 2}, {"salary", 25000}, {"experience", 6}};

        // Evaluate the combined rule against the data
        std::cout << "Data1 matches combined rule: " << (evaluate_rule(combined_rule, data1) ? "True" : "False") << std::endl;
        std::cout << "Data2 matches combined rule: " << (evaluate_rule(combined_rule, data2) ? "True" : "False") << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
