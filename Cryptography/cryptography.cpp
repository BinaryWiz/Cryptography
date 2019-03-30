#include <iostream>
#include <ios>
#include <fstream>
#include <string>
#include <Windows.h>
#include <ctime>
#include <vector>
#include <sstream>
using namespace std;

double determinant;

int encrypt_array[3][3];
double inverse_array[3][3];
int transpose_matrix[3][3];

string plaintext;


int calculate_descriminant(int, int, int, int);

int main() {
	while (1) {
		char user_response;
		cout << "Would you like to encrypt or decrypt? [e/d] ";
		cin >> user_response;

		void get_ascii_array();
		void generate_encryption_matrix();
		void generate_inverse_matrix();
		void generate_determinant();

		if (user_response == 'e') {
			cout << "What phrase do you want to encrypt? ";
			getline(cin, plaintext);
			getline(cin, plaintext);
			cout << "What would you like to call the file?" << endl;
			string file_name;
			getline(cin, file_name);
			int length_of_input = plaintext.length();
			int length_of_array = (length_of_input / 3);

			if (length_of_input % 3 > 0) {
				length_of_array++;
			}

			else;

			vector<vector<char>>orig_data(length_of_array, vector<char>(3));
			vector<vector<int>>ascii_data(length_of_array, vector<int>(3));
			vector<vector<int>>encrypted_data(length_of_array, vector<int>(3));

			for (int i = 0; i < plaintext.length(); i++) {
				char temp = plaintext.at(i);
				orig_data[i / 3][i % 3] = temp;
			}

			for (int i = 0; i < length_of_array; i++) {
				for (int x = 0; x < 3; x++) {
					ascii_data[i][x] = static_cast<int>(orig_data[i][x]);
				}
			}

			if (length_of_input % 3 > 0) {
				for (int x = length_of_input % 3; x < 3; x++) {
					ascii_data[length_of_array - 1][x] = -1;
				}
			}

			generate_encryption_matrix();

			for (int i = 0; i < length_of_array; i++) {
				for (int x = 0; x < 3; x++) {
					for (int y = 0; y < 3; y++) {
						encrypted_data[i][x] += encrypt_array[y][x] * ascii_data[i][x];
					}
				}
			}

			ofstream out_file;
			out_file.open(file_name + ".txt");
			out_file << length_of_array << "\n";
			for (int i = 0; i < length_of_array; i++) {
				for (int x = 0; x < 3; x++) {
					out_file << encrypted_data[i][x] << "\n";
				}
			}

			for (int i = 0; i < 3; i++) {
				for (int x = 0; x < 3; x++) {
					out_file << encrypt_array[i][x] << "\n";
				}
			}

			out_file.close();
		}

		if (user_response == 'd') {
			cout << "What file do you want to open? ";

			ifstream in_file;
			in_file.open("work.txt");

			int counter = 1;
			string temp;
			int array_length;
			getline(in_file, temp);
			stringstream geek(temp);
			geek >> array_length;
			vector<vector<int>>new_ascii_data(array_length, vector<int>(3));
			vector<vector<int>>unencrypted_data(array_length, vector<int>(3));

			for (int i = 0; i < array_length * 3; i++) {
				getline(in_file, temp);
				stringstream geek(temp);
				int temp_int;
				geek >> temp_int;
				new_ascii_data[i / 3][i % 3] = temp_int;
			}
			
			for (int i = 0; i < 3; i++) {
				for (int x = 0; x < 3; x++) {
					getline(in_file, temp);
					stringstream geek(temp);
					int temp_int;
					geek >> temp_int;
					encrypt_array[i][x] = temp_int;
				}
			}

			in_file.close();
			generate_determinant();
			generate_inverse_matrix();
			for (int i = 0; i < 3; i++) {
				for (int x = 0; x < 3; x++) {
					cout << inverse_array[i][x] << endl;
				}
			}

			for (int i = 0; i < array_length; i++) {
				for (int x = 0; x < 3; x++) {
					for (int y = 0; y < 3; y++) {
						unencrypted_data[i][x] += inverse_array[y][x] * new_ascii_data[i][x];
					}
				}
			}

			for (int i = 0; i < array_length; i++) {
				for (int x = 0; x < 3; x++) {
					cout << unencrypted_data[i][x] << endl;
				}
			}
		}
	}

	/*
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
	*/
	return 0;
}


void generate_determinant() {
	int right_row = (encrypt_array[0][0] * encrypt_array[1][1] * encrypt_array[2][2]) + (encrypt_array[1][0] * encrypt_array[2][1] * encrypt_array[2][2]) + (encrypt_array[2][0] * encrypt_array[0][1] * encrypt_array[1][2]);
	int left_row = (encrypt_array[0][2] * encrypt_array[1][1] * encrypt_array[2][0]) + (encrypt_array[1][2] * encrypt_array[2][1] * encrypt_array[0][0]) + (encrypt_array[2][2] * encrypt_array[0][1] * encrypt_array[1][0]);
	determinant = right_row - left_row;
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
