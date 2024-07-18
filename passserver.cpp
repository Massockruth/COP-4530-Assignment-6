#include "passserver.h"
#include "hashtable.h"
#include <crypt.h>

using namespace std;
using namespace cop4530;

PassServer::PassServer(size_t size) {
    htable.resizeTable(size);  // Initialize HashTable with the given size
}

PassServer::~PassServer() {
    htable.clear();  // Clear the hash table to release memory
}

bool PassServer::load(const char* filename) {
    return htable.load(filename);  // Load user data from file into hash table
}

bool PassServer::addUser(pair<string, string>& kv) {
    string encryptedstr = encrypt(kv.second);  // Encrypt the password
    pair<string, string> encryptedPair(kv.first, encryptedstr);
    return htable.insert(encryptedPair);  // Add user to hash table
}

bool PassServer::addUser(pair<string, string>&& kv) {
    pair<string, string> uncryptedPair(move(kv));
    return addUser(uncryptedPair);  // Forward to the regular addUser
}

bool PassServer::removeUser(const string& k) {
    return htable.remove(k);  // Remove user from hash table
}

bool PassServer::changePassword(const pair<string, string>& p, const string& newpassword) {
    if (p.second == newpassword) {
        return false;  // Same password, no change
    }
    
    if (!htable.contains(p.first)) {
        return false;  // User not found
    }
    
    string oldPassword = encrypt(p.second);
    string newPassword = encrypt(newpassword);
    
    pair<string, string> oldPair(p.first, oldPassword);
    if (!htable.match(oldPair)) {
        return false;  // Old password doesn't match
    }
    
    pair<string, string> newPair(p.first, newPassword);
    htable.insert(newPair);  // Update password
    return true;
}

bool PassServer::find(const string& user) const {
    return htable.contains(user);  // Check if user exists
}

void PassServer::dump() const {
    htable.dump();  // Dump hash table contents
}

size_t PassServer::size() const {
    return htable.getSize();  // Get size of hash table
}

bool PassServer::write_to_file(const char* filename) const {
    return htable.write_to_file(filename);  // Write hash table contents to file
}

string PassServer::encrypt(const string& str) {
    char salt[] = "$1$########";  // Salt for crypt function
    string cryptedstr = crypt(str.c_str(), salt);
    cryptedstr.replace(0, 12, "");  // Remove prefix
    return cryptedstr;  // Return encrypted password
}
