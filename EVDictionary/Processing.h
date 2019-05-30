#ifndef PROCESSING_H_INCLUDED
#define PROCESSING_H_INCLUDED

#include <map>
#include <string>
#include "word.h"
#include <FL/Fl.H>
#include <FL/Fl_Hold_Browser.H>

// Hàm load danh sách từ
std::map<std::string, word> loadWord(Fl_Hold_Browser* worddb);

// Hàm load danh sách từ được thêm vào
std::map<std::string, addWord> loadAddWord(Fl_Hold_Browser* worddb);

// Hàm load lịch sử tìm kiếm
std::map<std::string, int> loadHistory(Fl_Hold_Browser* worddb);

// Hàm load từ yêu thích
std::map<std::string, int> loadFavorite(Fl_Hold_Browser* worddb);

// Hàm trả về giá trị thập phân
int getDecimalValue(std::string str);

// Hàm kiểm tra một chuỗi có chứa ký tự '*' hay '@' hay không
int check(const char* w);

// Hàm chỉnh sửa hiển thị nghĩa của từ
std::string editMeaning(std::string meaning);

// Hàm chỉnh sửa hiển thị nghĩa của từ được thêm vào
std::string editAddMeaning(std::string meaning);

// Hàm lấy nghĩa của từ
std::string getMeaning(word w);

// Hàm thêm từ vào file "addword.dict"
void addWordToFile(const char* name, const char* wtype, const char* mean);

// Hàm xóa từ khỏi file "addword.dict"
void deleteWordFromFile(const char* w);

// Hàm thêm từ vào file "history.dict"
void addWordToHistoryFile(const char* w);

// Hàm xóa từ khỏi file "history.dict"
void deleteWordFromHistoryFile(const char* w);

// Hàm thêm từ vào file "favorite.dict"
void addWordToFavoriteFile(const char* w);

// Hàm xóa từ khỏi file "favorite.dict"
void deleteWordFromFavoriteFile(const char* w);

#endif // PROCESSING_H_INCLUDED