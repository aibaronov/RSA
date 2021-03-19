#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// Convert char vector to int vector
vector<int> returnVector(vector<char> vec) {
	int messageLength = vec.size();
	vector<int> messageInt(messageLength);

// ASCII value for " " is 32
// Spaces will be converted to zeros this way
// All other characters will be converted to their position in the alphabet
	for (int i = 0; i < messageLength; i++) {
		if (!isalnum(vec[i])) {
			messageInt[i] = (static_cast<int>(vec[i]) - 32);
		}
		else {
			messageInt[i] = (static_cast<int>(vec[i]) - 96);
		}
	}
// Print the new vector of integers
	
	cout << "The Original message is: " << endl;
	for (auto i : vec) {
		cout << i << " ";
	}
	cout << endl;
	cout << "The messages integer value is: " << endl;
	for (auto i : messageInt) {
		cout << i << " ";
	}
	cout << endl;
	
	return messageInt;
}
//Check to see if an integer is prime

bool primeCheck(int randomInt) {
	for (int i = 2; i < randomInt; i++) {
		if (randomInt % i == 0) {
			return false;
		}
	}
	return true;
}

//Choose a random prime number between 1 and 50

int primePicker() {

	srand((unsigned)time(0));
	int possiblePrime{};
	bool isNotPrime = true;

	while (isNotPrime) {

		possiblePrime = (rand() % 10) + 1;
		bool check = primeCheck(possiblePrime);
		if ((primeCheck(possiblePrime)) && (possiblePrime != 1)) {
			isNotPrime = false;
		}
		else
			isNotPrime = true;
	}
	return possiblePrime;

}

//Pick second prime value
int secondPrimePicker(int firstVal) {

	int possiblePrime{};
	bool isNotPrime = true;

	while (isNotPrime) {

		possiblePrime = (rand() % 10) + 1;
		bool check = primeCheck(possiblePrime);
		if (primeCheck(possiblePrime) && (firstVal != possiblePrime) && (possiblePrime != 1)) {
			isNotPrime = false;
		}
		else
			isNotPrime = true;
	}
	return possiblePrime;

}
//Convert vector of integers to a single value
long long convertToInt(vector<int> vec) {
	long long newInt{};
	int i{};
	int j{};
	int k{};
	int messageLength = vec.size();
	while (i < messageLength) {
		if (vec[i] >= 10) {

			j = vec[i] / 10;
			k = vec[i] % 10;
			newInt = newInt * 10 + j;
			newInt = newInt * 10 + k;
			i++;
		}
		else {
			newInt = newInt * 10 + vec[i];
			i++;
		}

	}
	return newInt;

}
//Find greatest common factor
int gcd(int a, int b) {
	if (a == 0 || b == 0) {
		return 0;
	}
	else if (a == b) {
		return a;
	}
	else if (a > b) {
		return gcd(a - b, b);
	}
	else 
		return gcd(a, b - a);
	}
	


//Generate public exponent
int publicExponent(int zVal) {
	int publicExp{};
	bool notCoPrime = true;
	while (notCoPrime) {
		publicExp = rand() % (zVal  + 2);
		if (gcd(publicExp, zVal) == 1) {
			notCoPrime = false;
		}
		else {
			notCoPrime = true;
		}
	}

	return publicExp;
}
//Extended Euclidean Algorithm
int extendedEuclidAlg(int a, int b, int* x, int* y) {
	if (a == 0) {
		*x = 0;
		*y = 1;
		return b;
	}
	int x1, y1;
	int gcd = extendedEuclidAlg(b % a, a, &x1, &y1);
	*x = y1 - (b / a) * x1;
	*y = x1;

	cout << "gcd(" << a << " , " << b << ")" << " = " << *x << "*" <<
		a << " + " << *y << "*" << b << endl;
	return *y;
}
//Generate private key
int privateKey(int zVal, int eVal) {
	int dVal{};
	int tVal{};
	int x, y;
	tVal = extendedEuclidAlg(zVal, eVal, &x, &y);
	dVal = tVal % zVal;
	cout << "d = " << tVal << " mod " << zVal << " = " << dVal << endl;
	return dVal;
}
//Encrypt Message
long long encryptMessage(int numMessage, int eVal, int nVal) {
	long long encrypted{};
	long long power = pow(numMessage, eVal);
	encrypted = power % nVal;
	cout << " c = m^e mod n = " << numMessage << "^" << eVal << " mod " << nVal << " = " << encrypted << endl;

	return encrypted;
}
//Decrypt Message
long long decryptMessage(int message, int dVal, int nVal) {
	long long decrypted{};
	long long power{};
	power = pow(message, dVal);
	decrypted = power % nVal;
	cout << " d = c^d mod n = " << message << "^" << dVal << " mod " << nVal << " = " << decrypted << endl;

	return decrypted;

}




int main() {

	// Read the message text file and save it to a string
	fstream newfile;
	string message;
	newfile.open("input.txt", ios::in);
	if (newfile.is_open()) {
		getline(newfile, message);
		newfile.close();
	}

	// Convert the message string to a vector of characters
	vector<char> messageVector(message.begin(), message.end());
	int message_Length = messageVector.size();

	// Convert vector of characters to vector of integers
	vector<int> numericMessage = returnVector(messageVector);
	cout << endl;

	long long messageAsNumber = convertToInt(numericMessage);
	cout << "Your numeric message is: " << messageAsNumber;
	cout << endl;

	//Boolalpha
	cout << boolalpha;
	
	cout << "**************************************" << endl;
	int firstPrime{};
	firstPrime = primePicker();
	cout << "First random prime = " << firstPrime << endl;
	int secondPrime{};
	secondPrime = secondPrimePicker(firstPrime);
	cout << "Second random prime = " << secondPrime << endl;

	//Compute public key
	int nVal{};
	nVal = firstPrime * secondPrime;
	cout << "n = " << nVal << endl;
	int zVal{};
	zVal = (firstPrime - 1) * (secondPrime - 1);
	cout << "z(n) = " << zVal << endl;
		//Compute public exponent
	int eVal{};
	eVal = publicExponent(zVal);
	cout << "Public exponent = " << eVal << endl;
		//public key as an array
	int publicKeyArray[2] = { nVal, eVal };
	cout << "The public key is: (" << publicKeyArray[0] << " , " << publicKeyArray[1] << ")" << endl;

	cout << "**************************************" << endl;

	//Extended Euclidean Algorithm Check
	int x, y;
	int tVal = extendedEuclidAlg(zVal, eVal, &x, &y);
	int dVal = privateKey(zVal, eVal);
	cout << "tVal: " << tVal << endl;
	cout << "dVal: " << dVal << endl;

	//Encrypt Message
	cout << "The encrypted messaged is: " << encryptMessage(messageAsNumber, eVal, nVal) << endl;
	//Decrypted Message
	cout << "The decrypted message is : " << decryptMessage(messageAsNumber, dVal, nVal) << endl;

	return 0;
	
}
