//
//  main.cpp
//  DataStruct_Prog_hw_3
//
//  Created by Michael Leong on 01/11/2022.
//

#include <iostream>
#include <termios.h>
#include <unistd.h>

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
            //return null char
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
            //return null char
            return 0;
        }
        
        //else
        return root->data;
    }
};

//tree node
//tree node data expects char
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

//Tree data expects char
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
    
    //computes the height of the tree
    int height(TreeNode *root) {
        if(!root) {
            return 0;
        }
        //else
        int lheight = height(root->left);
        int rheight = height(root->right);
        
        //use the larger one
        if(lheight > rheight) {
            return lheight+1;
        }
        //else
        return rheight+1;
    }
    
    void printCurrentLevel(TreeNode *root, int level) {
        if(!root) {
            return;
        }
        //else
        if(level == 1) {
            cout << root->data;
        } else if(level > 1) {
            printCurrentLevel(root->left, level-1);
            printCurrentLevel(root->right, level-1);
        }
    }
    
    void printLevelOrder() {
        for(int i = 1; i <= this->height(root); i++) {
            //print current level
            printCurrentLevel(root, i);
            //cout << '\n';
        }
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

double evalPostfix(string s, bool *valid) {
    MyStack<double> numStack;
    
    for(int i = 0; i < s.length(); i++) {
        //cout << "token: " << s[i] << '\n';
        
        if(isdigit(s[i])) {
            numStack.push(s[i]-48);
            //cout << s[i]-48 << '\n';
        } else {
            if(numStack.isEmpty()) {
                //invalid postfix
                //cout << "Invalid postfix\n";
                *valid = false;
                return 0;
            }
            double op1 = numStack.pop();
            
            if(numStack.isEmpty()) {
                //invalid postfix
                //cout << "Invalid postfix\n";
                *valid = false;
                return 0;
            }
            double op2 = numStack.pop();
            
            

            
            switch (s[i]) {
                case '+': {
                    
                    //cout << op2 << '+' << op1 << '=' << op2+op1 << '\n';
                    numStack.push(op2+op1);
                    break;
                }
                case '-': {
                    //cout << op2 << '-' << op1 << '=' << op2-op1 << '\n';
                    numStack.push(op2-op1);
                    break;
                }
                case '*': {
                    //cout << op2 << '*' << op1 << '=' << op2*op1 << '\n';
                    numStack.push(op2*op1);
                    break;
                }
                case '/': {
                    //cout << op2 << '/' << op1 << '=' << op2/op1 << '\n';
                    numStack.push(op2/op1);
                    break;
                }
                    
                default:
                    //invalid character
                    //cout << s[i] << "invalid character\n";
                    *valid = false;
                    break;
            }
        }
    }
    
    if(numStack.isEmpty()) {
        //cout << "stack is empty before pop invalid postfix\n";
        *valid = false;
    }
    double result = numStack.pop();
    if(!numStack.isEmpty()) {
        //cout << "stack is not empty invalid postfix\n";
        *valid = false;
    } else {
        //cout << "valid postfix\n";
        *valid = true;
    }
    
    return result;
}


//check char if it's '+', '-', '*', '/', '(', ')'
bool isBinaryOperator(char c) {
    if(c == 42 || c == 43 || c == 45 || c == 47 || c == 40 || c == 41) {
        return true;
    }
    
    //else
    return false;
}

bool validateSyntax(char c) {
    //cout << "c: " << c << '\n';
    
    //'0' to '9'
    if(isdigit(c)) {
        return true;
    } else if(isBinaryOperator(c)) {
        return true;
    }
    
    return false;
}

bool validateInfixSyntax(string infix) {
    char prevChar = 0;
    //check syntax
    for(int i = 0; i < infix.length(); i++) {
        if(!validateSyntax(infix[i])) {
            return false;
        }
        
        //don't accept more than single digit input
        if(isdigit(prevChar) && isdigit(infix[i])) {
            //cout << "prev: " << prevChar << " postfix[i]: " << infix[i] << '\n';
            return false;
        }
        prevChar = infix[i];
    }
    
    return true;
}

int mygetch( ) {
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

void UI() {
    char choice = 0;
    bool valid = false;
    
    do {
        string infix = "";
        
        cout << "Please enter an infix expression and press enter: ";
        cin.sync();
        choice = mygetch();
        
        if(choice == 27) {
            //cout << "Interrupt\n";
            cout << "received input: " << choice << '\n';
            break;
        } else {
            cout << choice;
        }
        
        cin >> infix;
        infix = choice + infix;
        infix = "(" + infix + ")";
        //cout << "new infix: "<< infix << '\n';
        
        if(!validateInfixSyntax(infix)) {
            cout << "Invalid infix syntax expression\n";
            continue;
        }
        
        Tree myTree = Tree(getExpressionTree(infix));
        string postfix = myTree.postOrder(myTree.root);
        string prefix = myTree.preOrder(myTree.root);
        string infix1 = myTree.inOrder(myTree.root);
        double evaluation = evalPostfix(postfix, &valid);
        
        if(valid) {
            cout << "The postfix expression: "<< postfix << '\n';
            cout << "The prefix expression: " << prefix << '\n';
            cout << "in order traversal: " << infix1 << '\n';
            cout << "=" << evaluation << '\n';
            cout << "level order traversal: ";
            myTree.printLevelOrder();
            //cout << '\n';
            cout << endl;
        } else {
            cout << "Invalid infix expression" << endl;
            continue;
        }
        
        //cout << "Enter any key and enter to continue or esc and enter to exit: ";
        //cin >> choice;
        
    } while(choice != 27);
    
    cout << " exit program\n";
}

int main(int argc, const char * argv[]) {
    //char ch = mygetch();
    //cout << "received input: " << ch << '\n';
    //cout << ch << endl;
    UI();
    
    return 0;
}
