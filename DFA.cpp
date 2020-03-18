#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
using namespace std;
ifstream I("input.txt");
ofstream O("output.txt");
struct State {
	map<char, int> states;
	bool is_final;
	void add_state(char l, int n) {
		states.insert(pair<char, int>(l,n));
	}
};
class DFA {
	vector<State> arrays;
	int start_index;
public:
	DFA(int n) { arrays.resize(n+1);}
	~DFA() { arrays.clear(); }
	void Init() {
		int fin_number;
		int fun_number;
		I >> start_index;
		I >> fin_number;
		for (int i = 0; i < fin_number; i++)
		{
			int final_index;
			I >> final_index;
			arrays[final_index].is_final = true;
		}
		I >> fun_number;
		for (int i = 0; i < fun_number; i++)
		{
			int from,to;
			char symbol;
			I >> from >> to >> symbol;
			arrays[from].add_state(symbol,to);
		}
	}
	bool IsRecognized(string s)
	{
		int current_index=start_index;
		State current_State = arrays[start_index];
		for (int i = start_index; i < s.size(); i++)
		{
			char symbol = s[i];
			map<char, int>::iterator it;
			it = current_State.states.find(symbol);
			if (it == current_State.states.end()) {
				return false;
			}
			else { current_index = it->second; }
			current_State = arrays[current_index];
		}
		if (current_State.is_final) { return true; }
		else { return false; }
	}
};

int main() {
	int number_of_states;
	I >> number_of_states;
	DFA dfa(number_of_states);
	dfa.Init();
	string word;
	int N;
	I >> N ;
	for (int i = 0; i < N; i++) {
		I >> word;
		if (dfa.IsRecognized(word)) { O << "YES" << "\n"; }
		else { O << "NO"<<"\n"; }
	}


}
