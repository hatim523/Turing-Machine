#include<iostream>
#include<string.h>
#include<string>

using namespace std;

/************************************************************************************/
/* Author: Hatim																	*/
/* Title: Turing Machine															*/
/* Currently built for {a^n b^n | n>0}												*/
/* Note: Create nodes before creating turing machine								*/
/* Please define the number of transitions from the outgoing node in constructor	*/
/************************************************************************************/

int node_num = 0;

class Node
{
private:
	int node;
	bool is_final;
	Node **next_at;
	int num_inputs;
	char **transition_function;
public:
	Node(int number_of_inputs_defined)
	{
		node = node_num++;
		num_inputs = number_of_inputs_defined;
		next_at = new Node*[num_inputs];
		is_final = 0;
		transition_function = new char*[num_inputs];
		for (int i = 0; i < num_inputs; i++)
			transition_function[i] = new char[3];
	}
	void transition_at_input(int input_number, char read, char write, Node *transit_state, char move)	//Transition will be mapped through input number
	{
		next_at[input_number] = transit_state;
		transition_function[input_number][0] = read;
		transition_function[input_number][1] = write;
		transition_function[input_number][2] = move;
	}
	int getRead(char symbol)
	{
		int num = -1;
		for (int i = 0; i < num_inputs; i++)
		{
			if (transition_function[i][0] == symbol)
			{
				num = i;
				break;
			}
		}
		return num;
	}
	char getWrite(int ref)
	{
		return transition_function[ref][1];
	}
	int getDirection(int ref)
	{
		if (transition_function[ref][2] == 'r' || transition_function[ref][2] == 'R')
			return 1;
		else
			return -1;
	}
	Node* getState(int ref)
	{
		return next_at[ref];
	}
	void make_final_state()
	{
		is_final = 1;
	}
	bool is_Final()
	{
		return is_final;
	}
};

class Turing_Machine
{
private:
	Node *head;
	char *input;
	int read_write_header;
public:
	Turing_Machine(char *in)
	{
		input = in;
		read_write_header = 3;
	}
	void Initial_State(Node *state)
	{
		head = state;
	}
	bool start_traversal()
	{
		Node *current_state = head;
		bool accepted = true;
		while (current_state != 0)
		{
			int transit_to = current_state->getRead(input[read_write_header]);
			if (transit_to >= 0)
			{
				input[read_write_header] = current_state->getWrite(transit_to);
				read_write_header += current_state->getDirection(transit_to);
				current_state = current_state->getState(transit_to);
			}
			else
			{
				if (current_state->is_Final())
				{
					accepted = true;
					current_state = 0;
				}
				else
				{
					current_state = 0;
					accepted = false;
				}
			}
		}
		return accepted;
	}
};

int main()
{
	string input;
	getline(cin, input);
	/*
	* Transfering string to tape
	*/
	char *tape = new char[input.size() + 7];
	tape[0] = '-';	// - treated as null character
	tape[1] = '-';
	tape[2] = '-';
	int i = 3;
	for (int j=0; j < input.size(); i++, j++)
	{
		tape[i] = input[j];
	}
	tape[i++] = '-';
	tape[i++] = '-';
	tape[i++] = '-';
	tape[i] = '\0';
	/*
	* Transfer complete
	*/

	//creating nodes
	Node *q0 = new Node(2);
	Node *q1 = new Node(3);
	Node *q2 = new Node(3);
	Node *q3 = new Node(2);
	Node *q4 = new Node(0);

	//transitions of q0
	q0->transition_at_input(0, 'a', 'x', q1, 'r');
	q0->transition_at_input(1, 'y', 'y', q3, 'r');
	//transitions of q1
	q1->transition_at_input(0, 'a', 'a', q1, 'r');
	q1->transition_at_input(1, 'y', 'y', q1, 'r');
	q1->transition_at_input(2, 'b', 'y', q2, 'l');
	//transitions of q2
	q2->transition_at_input(0, 'a', 'a', q2, 'l');
	q2->transition_at_input(1, 'y', 'y', q2, 'l');
	q2->transition_at_input(2, 'x', 'x', q0, 'r');
	//transitions of q3
	q3->transition_at_input(0, 'y', 'y', q3, 'r');
	q3->transition_at_input(1, '-', '-', q4, 'r');
	//making q4 final
	q4->make_final_state();

	Turing_Machine language(tape);
	language.Initial_State(q0);

	if (language.start_traversal())
		cout << "Accepted!";
	else
		cout << "Rejected!";
	return 0;
}