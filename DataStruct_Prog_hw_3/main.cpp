//
//  main.cpp
//  DataStruct_Prog_hw_3
//
//  Created by Michael Leong on 01/11/2022.
//

#include <iostream>

using namespace std;

//class to stack node
template<class T>
class StackNode {
public:
    T data;
    StackNode<T> *next;
    
public:
    StackNode<T>(T data) {
        this->data = data;
        this->next = nullptr;
    }
};

//class mystack
template<class T>
class MyStack {
public:
    StackNode<T> *root;
public:
    //constructor to initialize MyStack
    MyStack<T>() {
        root = nullptr;
    }
    
    //destructor must delete everything in the stack
    ~MyStack() {
        while(!isEmpty()) {
            this->pop();
        }
    }
    
    bool isEmpty() {
        return !root;
    }
    
    void push(T data) {
        StackNode<T> *stackNode = new StackNode(data);
        stackNode->next = root;
        this->root = stackNode;
    }
    
    T pop() {
        if(isEmpty()) {
            //return null character
            return 0;
        }
        
        //else
        StackNode<T> *temp = root;
        root = root->next;
        T popped = temp->data;
        delete temp;
        
        return popped;
    }
    
    T top() {
        if(isEmpty()) {
            //return null character
            return 0;
        }
        
        //else
        return root->data;
    }
};

//tree node
class TreeNode {
public:
    char data;
    TreeNode *left;
    TreeNode *right;
public:
    TreeNode() {
        this->data = 0;
        this->left = nullptr;
        this->right = nullptr;
    }
    
    TreeNode(char data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class Tree {
public:
    TreeNode *root;
    
public:
    Tree() {
        this->root = nullptr;
    }
    Tree(TreeNode *root) {
        this->root = root;
    }
    
    string postOrder(TreeNode *root) {
        string result = "";
        if (root) {
            result += postOrder(root->left);
            result += postOrder(root->right);
            result += root->data;
        }
        return result;
    }
    
    string preOrder(TreeNode *root) {
        string result = "";
        if(root) {
            result += root->data;
            result += preOrder(root->left);
            result += preOrder(root->right);
        }
        return result;
    }
    
    string inOrder(TreeNode *root) {
        string result = "";
        if(root) {
            result += inOrder(root->left);
            result +=  root->data;
            result += inOrder(root->right);
        }
        return result;
    }
    
    void printLevelOrder(TreeNode *root) {
        
    }
};

TreeNode *getExpressionTree(string s) {
    //stack to store nodes
    MyStack<TreeNode*> nodeStack;
    //stack to store characters
    MyStack<char> charStack;
    
    TreeNode *t = nullptr;
    TreeNode *t1 = nullptr;
    TreeNode *t2 = nullptr;
    
    //set precedence
    int p[123] = { 0 };
    p['+'] = 12;
    p['-'] = 12;
    p['*'] = 13;
    p['/'] = 13;
    p['%'] = 13;
    p['^'] = 14;
    p[')'] = 0;
    
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == '(') {
            charStack.push('(');
        } else if(isalpha(s[i]) || isdigit(s[i])) {
            t = new TreeNode(s[i]);
            //cout << t->data << '\n';
            nodeStack.push(t);
        } else if(p[s[i]] > 0) {
            //cout << "hi1\n";
            while(!charStack.isEmpty() && charStack.top() != '(' &&  ((s[i] != '^' && p[charStack.top()] >= p[s[i]]) || (s[i] == '^' && p[charStack.top()] > p[s[i]]))) {
                t = new TreeNode(charStack.pop());
                //cout << "test1\n";
                //cout << t->data << '\n';
                t1 = nodeStack.pop();
                t2 = nodeStack.pop();
                t->left = t2;
                t->right = t1;
                nodeStack.push(t);
                //cout << t->data << ' ' << t->left->data << ' ' << t->right->data << '\n';
            }
            charStack.push(s[i]);
        } else if(s[i] == ')') {
            //cout << "hi2\n";
            while(!charStack.isEmpty() &&  charStack.top() != '(') {
                t = new TreeNode(charStack.pop());
                //cout << "test2\n";
                //cout << t->data << '\n';
                t1 = nodeStack.pop();
                t2 = nodeStack.pop();
                t->left = t2;
                t->right = t1;
                nodeStack.push(t);
                //cout << t->data << ' ' << t->left->data << ' ' << t->right->data << '\n';
            }
            charStack.pop();
        }
    }
    t = nodeStack.top();
    
    return t;
}

double evalPostfix(string s) {
    MyStack<double> numStack;
    
    for(int i = 0; i < s.length(); i++) {
        //cout << "token: " << s[i] << '\n';
        
        if(isdigit(s[i])) {
            numStack.push(s[i]-48);
            //cout << s[i]-48 << '\n';
        } else {
            switch (s[i]) {
                case '+': {
                    double op1 = numStack.pop();
                    double op2 = numStack.pop();
                    //cout << op2 << '+' << op1 << '=' << op2+op1 << '\n';
                    numStack.push(op2+op1);
                    break;
                }
                case '-': {
                    double op1 = numStack.pop();
                    double op2 = numStack.pop();
                    //cout << op2 << '-' << op1 << '=' << op2-op1 << '\n';
                    numStack.push(op2-op1);
                    break;
                }
                case '*': {
                    double op1 = numStack.pop();
                    double op2 = numStack.pop();
                    //cout << op2 << '*' << op1 << '=' << op2*op1 << '\n';
                    numStack.push(op2*op1);
                    break;
                }
                case '/': {
                    double op1 = numStack.pop();
                    double op2 = numStack.pop();
                    //cout << op2 << '/' << op1 << '=' << op2/op1 << '\n';
                    numStack.push(op2/op1);
                    break;
                }
                    
                default:
                    break;
            }
        }
    }
    
    return numStack.top();
}

int main(int argc, const char * argv[]) {
    string infix;
    
    cout << "Please enter an infix expression and press enter: ";
    cin >> infix;
    infix = "(" + infix + ")";
    cout << "new infix: "<< infix << '\n';
    
    Tree myTree = Tree(getExpressionTree(infix));
    string postfix = myTree.postOrder(myTree.root);
    cout << "The postfix expression: "<< postfix << '\n';
    string prefix = myTree.preOrder(myTree.root);
    cout << "The prefix expression: " << prefix << '\n';
    string infix1 = myTree.inOrder(myTree.root);
    cout << "in order traversal: " << infix1 << '\n';
    
    cout << "evaluating postfix: " << evalPostfix(postfix) << '\n';
    
    
    return 0;
}
