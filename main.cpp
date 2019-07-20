/*
LCS - longest common subsequence
Implement and analyze the time complexity of an algorithm CountLCS that, given
n in the range [3:20], and two integers x and y that are each in the range
[0:2n-1], determines the number of distinct strings that are LCS's of
binstring(n,x) and binstring(n,y) and displays them.
*/

#include <iostream>
#include <cmath>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

// dp matrix for determining LCS and finding LCS strings
int** dp;

// handle the correctness of the inputs
int getn(int, int);
int getxy(char c, int low, int high);

// handle the transformence between binstring and value
int string2num(string str);
string binstring(int n, int num);

// determine the number of distinct strings that are LCS and record them
int LCS(string X, string Y, int n);
void findLCS(string X, string Y, int xi, int yi, string str, set<string>& ans);
int CountLCS(string X, string Y, int n, set<string>& ans);

string togglestr(int n);
string innerswap(string str, int n);

int main()
{

    int n, x, y;
    int z;

    n = getn(3, 20);
    z = pow(2, n) - 1;

    int maxx = -1;
    int xx = -1;
    int yy = -1;
    map<pair<string, string>, int> table;

    //int count = 0;
    //int THRESHOLD = z
    string Y = togglestr(n); cout << "finding Y = " << Y << " ..." << endl;
    for(x = 0; x<=z; x++){

        string X = binstring(n, x);

        set<string> ans;
        int lcs = CountLCS(X, Y, n, ans);

        pair<string, string> p (X, Y);
        table.insert( {p, ans.size()});

        if((int)ans.size() > maxx){
            maxx = ans.size();
            xx = x;
            yy = y;
        }

    }

    Y = innerswap(Y, n); cout << "finding Y = " << Y << " ..." << endl;
    for(x = ceil((float)n/2); x<=z; x++){

        string X = binstring(n, x);

        set<string> ans;
        int lcs = CountLCS(X, Y, n, ans);

        pair<string, string> p (X, Y);
        table.insert( {p, ans.size()});

        if((int)ans.size() > maxx){
            maxx = ans.size();
            xx = x;
            yy = y;
        }

    }

    cout << endl <<  "max = " << maxx << endl;

    for(auto it: table){
        if(it.second == maxx){
            string a = it.first.first;
            string b = it.first.second;

            cout << "x = " << string2num(a) <<  endl;
            cout << "y = " << string2num(b) << endl << endl;

            reverse(a.begin(), a.end());
            reverse(b.begin(), b.end());
            cout << "x = " << string2num(a) <<  endl;
            cout << "y = " << string2num(b) << endl << endl;
        }
    }

    //cout << endl << endl << xx << ", " << yy << endl;

    cout << endl;
}

string innerswap(string str, int n){
    int pos = ceil((float)n/2); //cout << pos << endl;
    swap(str[pos], str[pos+1]);
    return str;
}

string togglestr(int n){
    string s = "";
    for(int i=0; i<n; i++){
        if(i%2 == 0) s += "0";
        else s+= "1";
    }
    return s;
}

int string2num(string str){
	int num = 0;
	int shift = 0;
	for(int i = str.length() - 1; i >= 0; i--){
		if(str[i] == '1') num += pow(2, shift);
		shift++;
	}
	return num;
}

string binstring(int n, int num){
	string str;
	while (num > 0){
		int digit = num % 2;
		str.push_back(48 + digit);
		num /= 2;
        n--;
	}

    // add zeros if the size < n
    for(int i=0; i<n; i++) str.push_back(48);

	reverse(str.begin(), str.end());
	return str;
}

int LCS(string X, string Y, int n){
	// Build dp matrix
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {

            // row 0 and col 0 are the initial values
			if (i == 0 || j == 0)
                dp[i][j] = 0;

            // if character in X and Y are same, then increase the value by one
            // else keep the max value
			else
            {
                if (X[i - 1] == Y[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		    }
        }
	}
	return dp[n][n];
}

void findLCS(string X, string Y, int xi, int yi, string str, set<string>& ans)
{
    // base case: when reach the end of a string, add the current str into ans
    if(xi == 0 || yi == 0 || dp[xi][yi] == 0){
		ans.insert(str);
		return;
	}

    // If the last characters of X and Y are same, go diagonal
    if(X[xi - 1] == Y[yi - 1]){
        findLCS(X, Y, xi-1, yi-1, X[xi - 1]+str, ans);
    }

    // If the last characters of X and Y are not same, go to the direction with larger value
    // If the values are same, go both
    else{

        if( dp[xi - 1][yi] >= dp[xi][yi - 1] ){
            findLCS(X, Y, xi-1, yi, str, ans);
        }
        if( dp[xi][yi - 1] >= dp[xi - 1][yi] ){
            findLCS(X, Y, xi, yi-1, str, ans);
        }

    }
}

int CountLCS(string X, string Y, int n, set<string>& ans){

    // initialize dp matrix
    dp = new int*[n+1];
    for(int i=0; i<n+1; i++){
        dp[i] = new int[n+1];
    }

    // caculate LCS by building up dp matrix
    int lcs = LCS(X, Y, n);

    // find all distinct LCS strings
    findLCS(X, Y, n, n, "", ans);

    return lcs;
}

int getn(int low = 3, int high = 20){
    int n; // [3, 20]
    char again = 'n'; // control user input switch
    // get n
    while (again != 'y' || again != 'Y')
    {
        // instruction message
        cout <<"Please enter an integer between 3 and 20 as n: " << endl;
        // test if the input is an integer
        while (!(cin >> n)){
            cout << "Invalid character. Please enter an integer between " << low << " and " << high << " as n: " << endl;
            cin.clear();
            cin.ignore(100, '\n');
            if (cin >> n)
                break;
            else
                continue;
        }
        // test if the input is in the range [3, 20]
        if (n<low || n>high){
            cout << "Integer out of range. ";
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        // confirm the input
        while (n >= low && n <= high){
            cout << "You entered " << n << ". Confirm? (y/n)" << endl;
            cin >> again;
            break;
        }
        // if confirmed, turn off the switch and continue the inputs
        if (again == 'y' || again == 'Y')
            break;
        // if not, clear inputs and re-enter n value
        else
        {
            cin.clear();
            cin.ignore(100, '\n');\
        }
    }
    return n;
}

int getxy(char c, int low, int high){
    // initialize x or y
    int y;

    char again = 'n'; // control user input switch
    while (again != 'y' || again != 'Y')
    {
        // instruction message
        cout <<"Please enter an integer between " << low << " and " << high << " as " << c << ": " << endl;
        // test if the input is an integer
        while (!(cin >> y)){
            cout << "Invalid character. Please enter an integer between " << low << " and " << high << " as " << c << ": " << endl;
            cin.clear();
            cin.ignore(100, '\n');
            if (cin >> y)
                break;
            else
                continue;
        }
        // test if the input is in the range [3, 20]
        if (y < low || y > high){
            cout << "Integer out of range.";
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        // confirm the input
        while (y >= low && y <= high){
            cout << "You entered " << y << ". Confirm? (y/n)" << endl;
            cin >> again;
            break;
        }
        // if confirmed, turn off the switch and continue the inputs
        if (again == 'y' || again == 'Y')
            break;
        // if not, clear inputs and re-enter n value
        else
        {
            cin.clear();
            cin.ignore(100, '\n');\
        }
    }
    return y;
}
