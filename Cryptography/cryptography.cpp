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
			cin.ignore(100, '\n');
			getline(cin, plaintext);
			cout << "What would you like to call the file? ";
			string file_name;
			getline(cin, file_name);
			int length_of_input = plaintext.length();
			int length_of_array = (length_of_input / 3);

			if (length_of_input % 3 > 0) {
				length_of_array++;
			}

			else;

			// Creates the vectors needed for each step in the program
			vector<vector<char>>orig_data(length_of_array, vector<char>(3));
			vector<vector<int>>ascii_data(length_of_array, vector<int>(3));
			vector<vector<int>>encrypted_data(length_of_array, vector<int>(3));
			

			// Puts each character into an array
			for (int i = 0; i < plaintext.length(); i++) {
				char temp = plaintext.at(i);
				orig_data[i / 3][i % 3] = temp;
			}

			// Converts characters to ascii
			for (int i = 0; i < length_of_array; i++) {
				for (int x = 0; x < 3; x++) {
					ascii_data[i][x] = static_cast<int>(orig_data[i][x]);
				}
			}

			// Gets empty parts of the array and puts a negative in it
			if (length_of_input % 3 > 0) {
				for (int x = length_of_input % 3; x < 3; x++) {
					ascii_data[length_of_array - 1][x] = -1;
				}
			}

			// Populates the array for encryption
			generate_encryption_matrix();

			// Algorithm for multiplying the ascii data by the encrytion matrix
			for (int i = 0; i < length_of_array; i++) {
				for (int x = 0; x < 3; x++) {
					for (int y = 0; y < 3; y++) {
						encrypted_data[i][x] += encrypt_array[x][y] * ascii_data[i][y];
					}
				}
			}

			// Puts the encrypted data into the file
			ofstream out_file;
			out_file.open(file_name + ".txt");
			out_file << length_of_array << "\n";
			for (int i = 0; i < length_of_array; i++) {
				for (int x = 0; x < 3; x++) {
					out_file << encrypted_data[i][x] << "\n";
				}
			}

			// Puts the encryption key into the file
			for (int i = 0; i < 3; i++) {
				for (int x = 0; x < 3; x++) {
					out_file << encrypt_array[i][x] << "\n";
				}
			}

			// Closes the file
			out_file.close();
		}

		if (user_response == 'd') {
			ifstream in_file;
			cin.ignore(100, '\n');
			cout << "What file do you want to open? ";
			bool success = false;
			while (!success) {
				
				string file_name;
				getline(cin, file_name);
				in_file.open(file_name + ".txt");
				if (in_file.fail()) {
					cout << "Please enter a file that exists ";
					continue;
				}
				else {
					break;
				}
			}


			// For temporarily storing the numbers in the file
			string temp;

			// The number at the top of the file
			int array_length;
			getline(in_file, temp);

			// Allows me to convert the numbers to ints
			stringstream geek(temp);
			geek >> array_length;

			// Stores the encrypted data and the key in vectors
			vector<vector<int>>new_ascii_data(array_length, vector<int>(3));
			vector<vector<float>>unencrypted_data(array_length, vector<float>(3));
			string text;


			// Gets the encrypted ascii numbers
			for (int i = 0; i < array_length * 3; i++) {
				getline(in_file, temp);
				stringstream geek(temp);
				int temp_int;
				geek >> temp_int;
				new_ascii_data[i / 3][i % 3] = temp_int;
			}
			
			// Gets the encryption key
			for (int i = 0; i < 3; i++) {
				for (int x = 0; x < 3; x++) {
					getline(in_file, temp);
					stringstream geek(temp);
					int temp_int;
					geek >> temp_int;
					encrypt_array[i][x] = temp_int;
				}
			}

			// Closes the file
			in_file.close();

			// Gets the determinant of the encryption key
			generate_determinant();


			// Generates the inverse of the encryption key
			generate_inverse_matrix();

			// Multiplies the encrypted ascii by the inverse to get the original ascii
			for (int i = 0; i < array_length; i++) {
				for (int x = 0; x < 3; x++) {
					for (int y = 0; y < 3; y++) {
						unencrypted_data[i][x] += inverse_array[x][y] * new_ascii_data[i][y];

					}
				}
			}

			
			for (int i = 0; i < array_length; i++) {
				for (int x = 0; x < 3; x++) {
					int temp = (unencrypted_data[i][x] + 0.5) / 1;
					char character = temp;
					text += character;
				}
			}
			cout << text << endl;
		}
	}
	return 0;
}


void generate_determinant() {
	int right_row = (encrypt_array[0][0] * encrypt_array[1][1] * encrypt_array[2][2]) + (encrypt_array[0][1] * encrypt_array[1][2] * encrypt_array[2][0]) + (encrypt_array[0][2] * encrypt_array[1][0] * encrypt_array[2][1]);
	int left_row = (encrypt_array[2][0] * encrypt_array[1][1] * encrypt_array[0][2]) + (encrypt_array[2][1] * encrypt_array[1][2] * encrypt_array[0][0]) + (encrypt_array[2][2] * encrypt_array[1][0] * encrypt_array[0][1]);
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

	right_row = (encrypt_array[0][0] * encrypt_array[1][1] * encrypt_array[2][2]) + (encrypt_array[0][1] * encrypt_array[1][2] * encrypt_array[2][0]) + (encrypt_array[0][2] * encrypt_array[1][0] * encrypt_array[2][1]);
	left_row = (encrypt_array[2][0] * encrypt_array[1][1] * encrypt_array[0][2]) + (encrypt_array[2][1] * encrypt_array[1][2] * encrypt_array[0][0]) + (encrypt_array[2][2] * encrypt_array[1][0] * encrypt_array[0][1]);
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


	minor_matrix[0][0] = calculate_descriminant(5, 6, 8, 9);
	minor_matrix[0][1] = -1 * calculate_descriminant(4, 6, 7, 9);
	minor_matrix[0][2] = calculate_descriminant(4, 5, 7, 8);
	minor_matrix[1][0] = -1 * calculate_descriminant(2, 3, 8, 9);
	minor_matrix[1][1] = calculate_descriminant(1, 3, 7, 9);
	minor_matrix[1][2] = -1 * calculate_descriminant(1, 2, 7, 8);
	minor_matrix[2][0] = calculate_descriminant(2, 3, 5, 6);
	minor_matrix[2][1] = -1 * calculate_descriminant(1, 3, 4, 6);
	minor_matrix[2][2] = calculate_descriminant(1, 2, 4, 5);

	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
			inverse_array[i][x] = minor_matrix[i][x] * (1 / determinant);
		}
	}

}

int calculate_descriminant(int top_left, int top_right, int bottom_left, int bottom_right) {
	return (transpose_matrix[static_cast<int>((top_left - 1) / 3)][(top_left - 1) % 3] * transpose_matrix[static_cast<int>((bottom_right - 1) / 3)][(bottom_right - 1) % 3]) - (transpose_matrix[static_cast<int>((top_right - 1) / 3)][(top_right - 1) % 3] * transpose_matrix[static_cast<int>((bottom_left - 1) / 3)][(bottom_left - 1) % 3]);
}
