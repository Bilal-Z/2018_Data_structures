#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include "lists.h"
#include "stack.h"
#include "dsArray.h"
using namespace std;

int match = 1;
int mismatch = -1;
int gap = -1;

struct coOrds{
	int r;
	int c;
	// number of paths connected to this co-ordinate
	int p;
};

// helper function: read sequence from file
string getSequence(string s);

// helper function: get maximum of 3 integers
int getMax3(int a, int b, int c);

// helper function: reverse string using stack
string reverse(string s);

// generate scoring matrix
void genScoringMatrix(string s1, string s2, dsArray<int> &matrix, dsArray<string> &trace) {
	// first set 0, 0 to 0
	matrix(0, 0) = 0;
	trace(0, 0) = "x";
	// then set values of first row and first column
	for (int i = 1; i < matrix.getColumns(); i++) {
		matrix(0, i) = matrix(0, i - 1) + gap;
		trace(0, i) = "l";
	}

	for (int i = 1; i < matrix.getRows(); i++) {
		matrix(i, 0) = matrix(i - 1, 0) + gap;
		trace(i, 0) = "u";
	}

	// then calculate values for the rest of the matrix
	// take max value from up, left and diagonal

	int up, left, diag, j;
	string temp;
	for (int i = 1; i < matrix.getRows(); i++) {
		for (j = 1; j < matrix.getColumns(); j++) {
			temp = "";
			up = matrix(i - 1, j) + gap;
			left = matrix(i, j - 1) + gap;
			diag = matrix(i -1, j - 1);
			if (s1[j - 1] == s2[i - 1]) {
				diag += match;
			}
			else {
				diag += mismatch;
			}
			matrix(i, j) = getMax3(up, left, diag);

			// taking care of traceback matrix insertion
			if (matrix(i, j) == up) {
				temp += "u";
			}
			if(matrix(i, j) == left){
				temp += "l";
			}
			if (matrix(i, j) == diag) {
				temp += "d";
			}

			trace(i, j) = temp;
		}
	}
}

// gets paths of allignments
SLL<string> getAlignments(dsArray<int> &matrix, dsArray<string> &trace) {
	SLL<string> allPaths;
	stack<coOrds> fork;
	stack<string> prev;
	string path = "";
	string temp;
	int i = trace.getRows() - 1, j = trace.getColumns() - 1;
	while (temp != "x") {
		temp = trace(i, j);
		if (temp.length() > 1) {
			fork.push(coOrds{ i, j, (int)temp.length() - 2});
			prev.push(path);
			temp = temp[temp.length() - 1];
		}
		
		if (temp == "d") {
			i--;
			j--;
		}
		else if (temp == "u") {
			i--;
		}
		else {
			j--;
		}
	path += temp;
	}
	allPaths.appendSLL(path);

	coOrds branch;
	while (!fork.isEmpty()) {
		if (!prev.isEmpty()) {
			path = prev.pop();
		}
		else {
			path = "";
		}
		branch = fork.pop();
		temp = "not x";
		i = branch.r;
		j = branch.c;
		temp = trace(i, j)[branch.p];
		branch.p--;
		if (branch.p > -1) {
			fork.push(branch);
		}
		path += temp;
		if (temp == "d") {
			i--;
			j--;
		}
		else if (temp == "u") {
			i--;
		}
		else {
			j--;
		}
		while (temp != "x") {
			temp = trace(i, j);
			if (temp.length() > 1) {
				fork.push(coOrds{ i, j, (int)temp.length() - 2 });
				prev.push(path);
				temp = temp[temp.length() - 1];
			}

			if (temp == "d") {
				i--;
				j--;
			}
			else if (temp == "u") {
				i--;
			}
			else {
				j--;
			}
			path += temp;
		}
		allPaths.appendSLL(path);
	}
	return allPaths;
}


// get score of allignment
int getScore(dsArray<int> &matrix, string path) {
	int score = 0, i = matrix.getRows() - 1, j = matrix.getColumns() - 1;
	for (int k = 0; k < path.length() - 1; k++) {
		if (path[k] == 'd') {
			i--;
			j--;
		}
		else if (path[k] == 'u') {
			i--;
		}
		else {
			j--;
		}
		score += matrix(i, j);
	}
	return score;
}

// gives alligned strings
void stringAllign(string s1, string s2, dsArray<int> &matrix, SLL<string> paths) {
	int i, j;
	string p, o1 = "", o2 = "";

	for (int l = 0; l < paths.getSize(); l++) {
		p = paths[l].data;
		o1 = "", o2 = "";
		i = matrix.getRows() - 1;
		j = matrix.getColumns() - 1;
		for (int k = 0; k < p.length() - 1; k++) {
			if (p[k] == 'd') {
				o2 += s2[i - 1];
				o1 += s1[j - 1];
				i--;
				j--;
			}
			else if (p[k] == 'u') {
				o2 += s2[i - 1];
				o1 += "-";
				i--;
			}
			else {
				o2 += "-";
				o1 += s1[j - 1];
				j--;
			}
		}
		o1 = reverse(o1);
		o2 = reverse(o2);
		cout << o1 << endl;
		cout << o2 << endl;
		cout << getScore(matrix, p) << endl;
		cout << endl;
	}
	
}



// generate markov model of sequence
dsArray<double> markovModel(string s) {
	char states[] = { 'A', 'C', 'T', 'G' };
	dsArray<double> transition(4, 4);
	int j, sum;
	// initialize matrix to 0
	for (int i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			transition(i, j) = 0;
		}
	}
	// get absolute frequencies
	for (int i = 0; i < 4; i++) {
		for (j = 0; j < s.length() - 1; j++) {
			if (s[j] == states[i]) {
				if (s[j + 1] == 'A') {
					transition(i, 0) += 1;
				}
				else if (s[j + 1] == 'C') {
					transition(i, 1) += 1;
				}
				else if (s[j + 1] == 'T') {
					transition(i, 2) += 1;
				}
				else {
					transition(i, 3) += 1;
				}
			}
		}
	}
	// get percentages
	for (int i = 0; i < 4; i++) {
		sum = 0;
		for (j = 0; j < 4; j++) {
			sum += transition(i, j);
		}
		if (sum > 0) {
			for (j = 0; j < 4; j++) {
				transition(i, j) /= sum;
			}
		}
	}
	return transition;
}

struct nextProb {
	char N;
	double P;
};
ostream &operator<<(ostream &output, const nextProb &n) {
	output << n.N << ": " << n.P << " ";
	return output;
}

// generate random sequence given a markov model
string generateRandomSequence(dsArray<double> transition, int length) {
	char states[] = { 'A', 'C', 'T', 'G' };
	SLL<nextProb> nucProbs[4];
	string seq = "";
	int j;
	double random, sum, temp;
	for (int i = 0; i < 4; i++) {
		sum = 0;
		for (j = 0; j < 4; j++) {
			if (transition(i, j) == 0) {
				transition(i, j) = -1;
			}
			else {
				temp = transition(i, j);
				transition(i, j) += sum;
				sum += temp;
			}
		}
	}


	for (int i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (transition(i, j) != -1) {
				nucProbs[i].appendSLL({ states[j], transition(i, j) });
			}
		}
	}

	
	random = rand() % 4;
	if (random == 0) {
		seq += 'A';
	}
	else if (random == 1) {
		seq += 'C';
	}
	else if (random == 2) {
		seq += 'T';
	}
	else {
		seq += 'G';
	}

	for (int i = 1; i < length; i++) {
		random = rand() % 100;
		random /= 100;
		if (seq[i - 1] == 'A') {
			for (j = 0; j < nucProbs[0].getSize(); j++) {
				if (random < nucProbs[0][j].data.P) {
					seq += nucProbs[0][j].data.N;
					break;
				}
			}
		} else if (seq[i - 1] == 'C') {
			for (j = 0; j < nucProbs[1].getSize(); j++) {
				if (random < nucProbs[1][j].data.P) {
					seq += nucProbs[1][j].data.N;
					break;
				}
			}
		} else if (seq[i - 1] == 'T') {
			for (j = 0; j < nucProbs[2].getSize(); j++) {
				if (random < nucProbs[2][j].data.P) {
					seq += nucProbs[2][j].data.N;
					break;
				}
			}
		} else {
			for (j = 0; j < nucProbs[3].getSize(); j++) {
				if (random < nucProbs[3][j].data.P) {
					seq += nucProbs[3][j].data.N;
					break;
				}
			}
		}
	
	}
	return seq;
}


void getAlignSignificance(string s1, string s2) {
	SLL<string> bestPaths;
	SLL<int> scores;
	SLL<int> distinct;
	dsArray<int> scoring(s2.length() + 1, s1.length() + 1);
	dsArray<string> traceback(s2.length() + 1, s1.length() + 1);
	dsArray<double> markov = markovModel(s2);
	cout << "markov seq2: " << endl;
	markov.print();
	cout << endl;
	string randSeq;
	int j;
	for (int i = 0; i < 10; i++) {
		
		randSeq = generateRandomSequence(markov, s2.length());
		cout << randSeq << endl;
		genScoringMatrix(s1, randSeq, scoring, traceback);
		scoring.print();
		cout << endl;
		traceback.print();
		cout << endl;
		bestPaths = getAlignments(scoring, traceback);
		stringAllign(s1, randSeq, scoring, bestPaths);
		for (j = 0; j < bestPaths.getSize(); j++) {
			scores.appendSLL(getScore(scoring, bestPaths[j].data));
		}
	}
	scores.sort();
	scores.display();
	
	for (j = 0; j < scores.getSize(); j++) {
		if (!distinct.existsIn(scores[j].data)) {
			distinct.appendSLL(scores[j].data);
		}
	}
	cout << endl;
	double sum = 0;
	int *frequencies = new int[distinct.getSize()];
	
	for (int i = 0; i < distinct.getSize(); i++) {
		frequencies[i] = 0;
		for (j = 0; j < scores.getSize(); j++) {
			if (distinct[i].data == scores[j].data) {
				frequencies[i] += 1;
			}
		}
		sum += frequencies[i];
	}
	double *probabilities = new double[distinct.getSize()];
	for (int i = 0; i < distinct.getSize(); i++) {
		probabilities[i] = frequencies[i] / sum;
	}


	cout << endl;
	cout << sum << endl;
	for (int i = 0; i < distinct.getSize(); i++) {
		cout << distinct[i].data << ": " << frequencies[i] << ": " << probabilities[i] << endl;
	}
	
}

int main() {
	srand(time(NULL));
	string seq1 = getSequence("seq1.txt");
	string seq2 = getSequence("seq2.txt");

	cout << seq1 << endl;
	cout << seq2 << endl;

	dsArray<int> scoring(seq2.length() + 1, seq1.length() + 1);

	//points to previous index from which current is derived
	dsArray<string> traceback(seq2.length() + 1, seq1.length() + 1);

	genScoringMatrix(seq1, seq2, scoring, traceback);

	scoring.print();
	cout << endl;
	traceback.print();
	cout << endl;
	SLL<string> bestPaths = getAlignments(scoring, traceback);
	bestPaths.display();
	cout << endl;
	stringAllign(seq1, seq2, scoring, bestPaths);

	cout << "<<<<<<<<<<<<<<<<<<<<<<<RANDOMS>>>>>>>>>>>>>>>>>>>>>>>>>"<< endl;
	cout << endl;
	getAlignSignificance(seq1, seq2);
	return 0;
}

string getSequence(string s) {
	ifstream in(s);
	string seq = "";
	char temp;
	while (!in.eof()) {
		temp = 0;
		in.get(temp);
		if (temp) {
			seq += temp;
		}
	}
	return seq;
}

int getMax3(int a, int b, int c) {
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

string reverse(string s) {
	stack<char> rev;
	string flipped = "";
	for (int i = 0; i < s.length(); i++) {
		rev.push(s[i]);
	}
	for (int i = 0; i < s.length(); i++) {
		flipped += rev.pop();
	}
	return flipped;
}