# Turing Machine Model
Turing Machine implemented using Linked List structure. Example implementation of language is given. Can be used to built for any language.

//Visual Studio Project

Steps to implement any language:
  1) Create nodes equivalent to states in your turing machine model.
  2) Pass number of transitions defined at that node in the constructor (Important).
  3) If any final state exist, make it final by calling the relevant function.
  4) Create object of turing machine and pass the tape(string created) in the constructor.
  5) Pass the initial state of the model in relevant function of turing machine object.
  6) Start traversal through the nodes in machine.
              If language is accepted:
                the function will return 1
              else
                function will return 0;
