#include <stdlib.h>
#include <string>

int guessUsersNumber(int low, int high) {
	if (high == low) {
		return high;
	}

	int query = (high + low) / 2;
	cout << "Is your number higher or lower than " << query << "?" << endl;
	string resp;
	cin >> resp;
	if (resp.at(0) == 'h') {
		return guessUsersNumber(query, high);
	} else if (resp.at(0) == 'l') {
		return guessUsersNumber(low, query);
	} else {
		return query;
	}

	return -1;
}
