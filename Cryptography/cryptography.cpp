#include <iostream>
#include <ios>
#include <string>
#include <Windows.h>
#include <ctime>
#include <vector>
using namespace std;

char orig_data[3][3];
int ascii_data[3][3];
int encrypt_array[3][3];
double inverse_array[3][3];
int transpose_matrix[3][3];
double determinant;

string plaintext;

int calculate_descriminant(int, int, int, int);

int main() {
	void get_ascii_array();
	void generate_encryption_matrix();
	void generate_inverse_matrix();
	getline(cin, plaintext);
	int length_of_input = plaintext.length();
	int length_of_array = (length_of_input / 3) + ((length_of_input % 3) / 3);
	cout << length_of_input;
	vector<vector<char>>orig_data(length_of_array, vector<char>(3));


	for (int i = 0; i < plaintext.length(); i++) {
		char temp = plaintext.at(i);
		orig_data[i / 3][i % 3] = temp;
	}

	cout << length_of_array << endl;
	for (int i = 0; i < length_of_array; i++) {
		for (int x = 0; x < 3; x++) {
			cout << orig_data[i][x] << "Mafuger" << endl;
		}
	}

	

	get_ascii_array();
	generate_encryption_matrix();
	generate_inverse_matrix();

	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
			cout << encrypt_array[i][x] << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
			cout << inverse_array[i][x] << " ";
		}
	}

	return 0;
}

void get_ascii_array() {
	// Generates an ascii array from the 
	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
			ascii_data[i][x] = static_cast<int>(orig_data[x][i]);
		}
	}
}

void generate_encryption_matrix() {
	srand(time(0));
	int right_row;
	int left_row;
	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
			encrypt_array[i][x] = rand() % 100 + 1;
		}
	}

	right_row = (encrypt_array[0][0] * encrypt_array[1][1] * encrypt_array[2][2]) + (encrypt_array[1][0] * encrypt_array[2][1] * encrypt_array[2][2]) + (encrypt_array[2][0] * encrypt_array[0][1] * encrypt_array[1][2]);
	left_row = (encrypt_array[0][2] * encrypt_array[1][1] * encrypt_array[2][0]) + (encrypt_array[1][2] * encrypt_array[2][1] * encrypt_array[0][0]) + (encrypt_array[2][2] * encrypt_array[0][1] * encrypt_array[1][0]);
	determinant = right_row - left_row;
	
	if (determinant == 0) {
		generate_encryption_matrix();
	}
}

void generate_inverse_matrix() {
	int minor_matrix[3][3];
	int numbers[3] = { 1, 2, 3 };

	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
			transpose_matrix[x][i] = encrypt_array[i][x];
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
			minor_matrix[0][0] = calculate_descriminant(5, 6, 8, 9);
			minor_matrix[0][1] = -1 * calculate_descriminant(4, 6, 7, 9);
			minor_matrix[0][2] = calculate_descriminant(4, 5, 7, 8);
			minor_matrix[1][0] = -1 * calculate_descriminant(2, 3, 8, 9);
			minor_matrix[1][1] = calculate_descriminant(1, 3, 7, 9);
			minor_matrix[1][2] = -1 * calculate_descriminant(1, 2, 7, 8);
			minor_matrix[2][0] = calculate_descriminant(2, 3, 5, 6);
			minor_matrix[2][1] = -1 * calculate_descriminant(1, 3, 4, 6);
			minor_matrix[2][2] = calculate_descriminant(1, 2, 4, 5);
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
			inverse_array[i][x] = minor_matrix[i][x] * (1 / determinant);
		}
	}

}

int calculate_descriminant(int top_left, int top_right, int bottom_left, int bottom_right) {
	return (transpose_matrix[static_cast<int>((top_left - 1) / 3)][(top_left - 1) % 3] * transpose_matrix[static_cast<int>((bottom_right - 1) / 3)][(bottom_right - 1) % 3]) - (transpose_matrix[static_cast<int>((top_right - 1) / 3)][(top_right - 1) % 3] * transpose_matrix[static_cast<int>((bottom_left - 1) / 3)][(bottom_left - 1) % 3]);
}
