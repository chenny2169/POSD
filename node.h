#ifndef NODE_H
#define NODE_H

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}

  bool evaluate(){
    if (payload == COMMA){
      return (left -> evaluate() && right -> evaluate());
    }
    else if (payload == SEMICOLON){
      bool leftBool = left -> evaluate();
      bool rightBool = right -> evaluate();
      return (leftBool || rightBool);
    }
    else if (payload == EQUALITY){
      return (left -> term -> match(*(right -> term)));
    }
    return false;
  }
    // while (left != 0 && right != 0){
    //   left -> evaluate();
    //   right -> evaluate();
    //   if (left -> payload == TERM && right -> payload == TERM && this -> payload == EQUALITY){
    //      boolVector.push_back((left -> term) -> match(*(right -> term)));
    //   }
    //   else{
    //     for (int i = 0; i < boolVector.size(); i++){
    //       if (this -> payload == COMMA){
    //         boolVector.push_back((boolVector[0] && boolVector[i]));
    //         boolVector.erase(boolVector.begin(), boolVector.begin() + 2);
    //       }
    //       else if (this -> payload == SEMICOLON){
    //         boolVector.push_back((boolVector[0] || boolVector[i]));
    //         boolVector.erase(boolVector.begin(), boolVector.begin() + 2);
    //       }
    //     }
    //     break;
    //   }
    // }
  // }

  string convertEnumToString(Operators op){
    switch (op){
      case SEMICOLON:
        return ";";
        break;
      case COMMA:
        return ",";
        break;
      case EQUALITY:
        return "=";
        break;
      default:
        return term -> symbol();
    }
  }

  Operators payload;
  Term * term;
  Node * left;
  Node * right;
  std::vector<bool> boolVector;
  std::vector<Node *> nodeVector;
};

#endif
