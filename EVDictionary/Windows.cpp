#include <FL/Fl.H> 
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <fstream>
#include <iostream>
#include <map>
#include <cstdio>
#include <string>
#include "word.h"
#include "Processing.h"
#include "Windows.h"

using namespace std;

map<string, word> dictionary;
map<string, addWord> dictionary_add;
map<string, int> historyword;
map<string, int> favoriteword;

Fl_Hold_Browser* word_db;
Fl_Hold_Browser* addword_db;
Fl_Hold_Browser* history_db;
Fl_Hold_Browser* favorite_db;

MainWindow::MainWindow(int w, int h, const char* title) :Fl_Window(w, h, title) {

	begin();

	resizable(this);

	this->icon();
	this->callback(cb_quit, this);
	this->color((Fl_Color)(140));
	

	Fl_Tabs* tab = new Fl_Tabs(0, 0, 1220, 645); {

		tab->labelcolor(FL_BLUE);
		tab->color2((Fl_Color)(140));

		// Tab "Trang chủ"

		Fl_Group* home = new Fl_Group(0, 35, 1200, 610, u8"Trang chủ"); {

			home->color((Fl_Color)(140));
			home->color2((Fl_Color)(140));
			home->labelfont(FL_BOLD);
			home->labelsize(16);

			title1 = new Fl_Box(800, 65, 180, 20, u8"Từ điển Anh Việt");
			title1->box(FL_NO_BOX);
			title1->labelcolor(FL_BLUE);
			title1->labelsize(50);
			title1->labelfont(FL_HELVETICA_BOLD);
			title1->labeltype(FL_SHADOW_LABEL);

			translate = new Fl_Button(280, 50, 70, 50, "@search");
			translate->callback(cb_print, this);

			quit = new Fl_Button(1080, 575, 70, 50, u8"Thoát");
			quit->callback(cb_quit, this);

			inp = new Fl_Input(50, 50, 200, 50, "");
			inp->callback(cb_print, this);
			inp->output();

			out = new Fl_Text_Display(280, 120, 900, 410, "");
			buff = new Fl_Text_Buffer();
			out->buffer(buff);

			add_fav = new Fl_Button(850, 575, 170, 50, u8"Thêm vào từ yêu thích");
			add_fav->callback(cb_add_fav, this);

			word_db = new Fl_Hold_Browser(50, 120, 200, 410, "");
			word_db->color((Fl_Color)(25));
			word_db->textcolor((Fl_Color)(4));
			dictionary = loadWord(word_db);
			dictionary_add = loadAddWord(word_db);
			word_db->value(60);
			word_db->callback(cb_db, this);

		}

		home->end();

		//Tab "Thêm từ"

		Fl_Group* addwordgr = new Fl_Group(0, 35, 1200, 610, u8"Thêm từ"); {

			addwordgr->active();
			addwordgr->color((Fl_Color)(140));
			addwordgr->color2((Fl_Color)(140));
			addwordgr->labelfont(FL_BOLD);
			addwordgr->labelsize(16);

			title1 = new Fl_Box(800, 65, 180, 20, u8"Từ điển Anh Việt");
			title1->box(FL_NO_BOX);
			title1->labelcolor(FL_BLUE);
			title1->labelsize(50);
			title1->labelfont(FL_HELVETICA_BOLD);
			title1->labeltype(FL_SHADOW_LABEL);

			newWord = new Fl_Input(100, 100, 500, 50, u8"Từ cần thêm");
			newWord->labelfont(FL_BOLD);

			type = new Fl_Input(100, 200, 500, 50, u8"Từ loại");
			type->labelfont(FL_BOLD);

			newMeaning = new Fl_Multiline_Input(100, 300, 500, 200, u8"Nghĩa của từ");
			newMeaning->labelfont(FL_BOLD);

			add = new Fl_Button(430, 550, 70, 50, u8"Thêm");
			add->callback(cb_addword, this);

			cancel = new Fl_Button(530, 550, 70, 50, u8"Hủy");
			cancel->callback(cb_cancel, this);

			wdelete = new Fl_Button(330, 550, 70, 50, u8"Xóa");
			wdelete->callback(cb_delete, this);

			wchange = new Fl_Button(230, 550, 70, 50, u8"Sửa");
			wchange->callback(cb_change, this);

			addword_db = new Fl_Hold_Browser(730, 200, 270, 300, "");
			addword_db->color((Fl_Color)(25));
			addword_db->textcolor((Fl_Color)(4));
			loadAddWord(addword_db);
			for (int i = 0; i < 20; i++) {
				addword_db->add(" ");
			}
			addword_db->callback(cb_adddb, this);

			Fl_Box* db_title = new Fl_Box(730, 150, 270, 50, u8"Các từ đã thêm");
			db_title->labelsize(25);
			db_title->labelfont(FL_HELVETICA_BOLD);

		}

		addwordgr->end();

		//Tab "Lịch sử"

		Fl_Group* history = new Fl_Group(0, 35, 1200, 610, u8"Lịch sử"); {

			history->color((Fl_Color)(140));
			history->color2((Fl_Color)(140));
			history->labelfont(FL_BOLD);
			history->labelsize(16);

			title1 = new Fl_Box(800, 65, 180, 20, u8"Từ điển Anh Việt");
			title1->box(FL_NO_BOX);
			title1->labelcolor(FL_BLUE);
			title1->labelsize(50);
			title1->labelfont(FL_HELVETICA_BOLD);
			title1->labeltype(FL_SHADOW_LABEL);

			history_db = new Fl_Hold_Browser(50, 120, 200, 410, "");
			history_db->color((Fl_Color)(25));
			history_db->textcolor((Fl_Color)(4));
			historyword = loadHistory(history_db);
			history_db->callback(cb_his_print, this);

			Fl_Box* his_title = new Fl_Box(50, 70, 200, 50, u8"Tìm kiếm gần đây");
			his_title->labelsize(25);
			his_title->labelfont(FL_HELVETICA_BOLD);

			his_out = new Fl_Text_Display(280, 120, 900, 410, "");
			his_buff = new Fl_Text_Buffer();
			his_out->buffer(his_buff);

			his_delete = new Fl_Button(680, 560, 200, 50, u8"Xóa khỏi lịch sử tìm kiếm");
			his_delete->callback(cb_his_del, this);

		}

		history->end();

		// Tab "Từ yêu thích"
		
		Fl_Group* favorite = new Fl_Group(0, 35, 1200, 610, u8"Từ yêu thích"); {

			favorite->color((Fl_Color)(140));
			favorite->color2((Fl_Color)(140));
			favorite->labelfont(FL_BOLD);
			favorite->labelsize(16);

			title1 = new Fl_Box(800, 65, 180, 20, u8"Từ điển Anh Việt");
			title1->box(FL_NO_BOX);
			title1->labelcolor(FL_BLUE);
			title1->labelsize(50);
			title1->labelfont(FL_HELVETICA_BOLD);
			title1->labeltype(FL_SHADOW_LABEL);

			favorite_db = new Fl_Hold_Browser(50, 120, 200, 410, "");
			favorite_db->color((Fl_Color)(25));
			favorite_db->textcolor((Fl_Color)(4));
			favoriteword = loadFavorite(favorite_db);
			favorite_db->callback(cb_fav_print, this);

			Fl_Box* fav_title = new Fl_Box(50, 70, 200, 50, u8"Từ yêu thích");
			fav_title->labelsize(25);
			fav_title->labelfont(FL_HELVETICA_BOLD);

			fav_out = new Fl_Text_Display(280, 120, 900, 410, "");
			fav_buff = new Fl_Text_Buffer();
			fav_out->buffer(fav_buff);

			fav_delete = new Fl_Button(680, 560, 200, 50, u8"Xóa khỏi từ yêu thích");
			fav_delete->callback(cb_fav_del, this);

		}

		favorite->end();
		
	}

	tab->end();
	show();
	Fl::run();

}

MainWindow::~MainWindow() {}

void MainWindow::cb_quit(Fl_Widget*, void* v) {
	
	((MainWindow*)v)->cb_quit_i();

}

// Thoát khỏi chương trình
void MainWindow::cb_quit_i() {

	exit(0);
	end();

}

// Chỉnh sửa màu sắc nghĩa của từ trước khi hiển thị ra màn hình
void MainWindow::edit_meaning(Fl_Text_Display* out, int nlen, int len) {

	Fl_Text_Display::Style_Table_Entry stable[] = {
		// FONT COLOR      FONT FACE   FONT SIZE
		// --------------- ----------- --------------
		{  FL_RED,         FL_COURIER, 16 }, // A - Red
		{  FL_BLUE,        FL_COURIER, 16 }, // B - Blue
	};

	Fl_Text_Buffer *sbuff = new Fl_Text_Buffer();
	int stable_size = sizeof(stable) / sizeof(stable[0]);
	out->highlight_data(sbuff, stable, stable_size, 'A', 0, 0);

	string f = "";
	for (int i = 0; i < nlen; i++) {
		f += "A";
	}
	for (int i = 0; i < len - nlen; i++) {
		f += "B";
	}

	sbuff->text(f.c_str());

	this->show();
	Fl::run();	

}

void MainWindow::cb_print(Fl_Widget*, void* v) {

	((MainWindow*)v)->cb_print_i();
	
}

// Hiển thị nghĩa của từ ra màn hình
void MainWindow::cb_print_i() {

	buff->text("");

	const char* keyWord = inp->value();
	string b = keyWord;
	int nlen = b.length();
	int len;

	_strlwr_s((char*)keyWord, b.length() + 1);
	word result = dictionary[keyWord];
	addWord result2 = dictionary_add[keyWord];

	if (!result.isNull() || !result2.isNull()) {

		// Thêm từ vào lịch sử tìm kiếm
		if (historyword[keyWord] < 1 || historyword[keyWord] > 31) {
			addWordToHistoryFile(keyWord);
			history_db->clear();
			historyword = loadHistory(history_db);
		}
		else {
			deleteWordFromHistoryFile(keyWord);
			addWordToHistoryFile(keyWord);
			history_db->clear();
			historyword = loadHistory(history_db);
		}

		if (history_db->text(31)[0] != ' ') {
			deleteWordFromHistoryFile(history_db->text(31));
			history_db->clear();
			historyword = loadHistory(history_db);
		}

		// Hiển thị nghĩa của từ ra màn hình
		if (!result.isNull()) {
			word_db->value(result.getNum());
			string meaning = getMeaning(result);
			len = meaning.length();
			const char* a = meaning.c_str();
			buff->text(a);
			edit_meaning(out, nlen, len);
		}
		else {
			word_db->value(result2.getNum());
			string meaning = editAddMeaning(result2.getMeaning());
			len = meaning.length();
			const char* b = meaning.c_str();
			buff->text(b);
			edit_meaning(out, nlen, len);
		}	
	}

	end();

}

void MainWindow::cb_addword(Fl_Widget*, void* v) {

	((MainWindow*)v)->cb_addword_i();
	
}

// Hàm thêm từ
void MainWindow::cb_addword_i() {

	const char* name = newWord->value();
	const char* wtype = type->value();
	const char* mean = newMeaning->value();
	string w = name;

	if (!name[0] || !wtype[0] || !mean[0])
		fl_message(u8"Bạn phải điền đầy đủ các mục!");
	else if (name[0] == ' ')
		fl_message(u8"Xóa dấu cách trước tên từ!");
	else if (name[w.length() - 1] == ' ')
		fl_message(u8"Xóa dấu cách sau tên từ!");
	else {
		word test1 = dictionary[name];
		addWord test2 = dictionary_add[name];

		if (!test1.isNull()) {
			fl_message(u8"Từ đã tồn tại");
		}
		else if (!test2.isNull()) {

			int rep = fl_choice(u8"Từ đã được thêm vào!", u8"Cập nhật", u8"Đóng", u8"Xóa");

			if (rep == 0) {
				cb_change_i();
			}
			else if (rep == 2) {
				cb_delete_i();
			}
		}
		else {

			if (check(name) && check(wtype) && check(mean)) {   // Kiểm tra name, wtype, mean có chứa ký tự 
																// * hay @ hay không.
				addWordToFile(name, wtype, mean);

				// Cập nhật mục từ được thêm vào
				addword_db->clear();
				loadAddWord(addword_db);
				for (int i = 0; i < 20; i++) {
					addword_db->add(" ");
				}

				//Cập nhật danh sách từ
				word_db->clear();
				dictionary = loadWord(word_db);
				dictionary_add = loadAddWord(word_db);
				fl_message(u8"Đã thêm từ thành công!");

				newWord->value("");
				type->value("");
				newMeaning->value("");
				word_db->value(60);
				buff->text("");
			}
			else
				fl_message(u8"Không được chứa ký tự * và @");
		}
	}
	end();

}

void MainWindow::cb_cancel(Fl_Widget*, void* v) {

	((MainWindow*)v)->cb_cancel_i();

}

// Hàm hủy thêm từ
void MainWindow::cb_cancel_i() {

	newWord->value("");
	type->value("");
	newMeaning->value("");
	end();

}

void MainWindow::cb_db(Fl_Widget*, void* v) {

	((MainWindow*)v)->cb_db_i();

}

void MainWindow::cb_db_i() {

	int index = word_db->value();
	inp->value(word_db->text(index));
	cb_print_i();
	end();

}

void MainWindow::cb_adddb(Fl_Widget*, void* v) {

	((MainWindow*)v)->cb_adddb_i();

}

void MainWindow::cb_adddb_i() {

	int index = addword_db->value();
	const char* w = addword_db->text(index);
	addWord result = dictionary_add[w];

	newWord->value(result.getName().c_str());
	type->value(result.getType().c_str());
	newMeaning->value(result.getInp_mean().c_str());
	end();
	
}

void MainWindow::cb_delete(Fl_Widget*, void* v) {

	((MainWindow*)v)->cb_delete_i();

}

// Hàm xóa từ
void MainWindow::cb_delete_i() {

	const char* w = newWord->value();
	addWord test = dictionary_add[w];
	
	if (!test.isNull()) {

		deleteWordFromFile(w);

		addword_db->clear();
		loadAddWord(addword_db);

		word_db->clear();
		dictionary = loadWord(word_db);
		dictionary_add = loadAddWord(word_db);
		buff->text("");

		deleteWordFromHistoryFile(w);
		history_db->clear();
		historyword = loadHistory(history_db);

		deleteWordFromFavoriteFile(w);
		favorite_db->clear();
		favoriteword = loadFavorite(favorite_db);

		newWord->value("");
		type->value("");
		newMeaning->value("");

	}

	end();

}

void MainWindow::cb_change(Fl_Widget*, void* v) {

	((MainWindow*)v)->cb_change_i();

}

// Hàm sửa từ
void MainWindow::cb_change_i() {

	const char* name = newWord->value();
	const char* wtype = type->value();
	const char* mean = newMeaning->value();

	if (!name[0] || !wtype[0] || !mean[0])
		fl_message(u8"Bạn phải điền đầy đủ các mục!");
	else {

		addWord test = dictionary_add[name];

		if (!test.isNull()) {

			// Xóa từ hiện tại
			cb_delete_i();

			// Thêm từ đã được sửa
			addWordToFile(name, wtype, mean);
			addword_db->clear();
			loadAddWord(addword_db);
			for (int i = 0; i < 20; i++) {
				addword_db->add(" ");
			}

			word_db->clear();
			dictionary = loadWord(word_db);
			dictionary_add = loadAddWord(word_db);
			fl_message(u8"Đã sửa từ thành công!");
			word_db->value(60);
			buff->text("");
		}
	}

	end();

}

void MainWindow::cb_his_print(Fl_Widget*, void* v) {

	((MainWindow*)v)->cb_his_print_i();

}

// Hiển thị nghĩa của từ trong lịch sử tìm kiếm
void MainWindow::cb_his_print_i() {

	his_buff->text("");

	int index = history_db->value();
	const char* keyWord = history_db->text(index);
	string b = keyWord;
	int nlen = b.length();
	int len;

	word result = dictionary[keyWord];
	addWord result2 = dictionary_add[keyWord];

	if (!result.isNull() || !result2.isNull()) {
		if (!result.isNull()) {
			string meaning = getMeaning(result);
			len = meaning.length();
			const char* a = meaning.c_str();
			his_buff->text(a);
		}
		else {
			string meaning = editAddMeaning(result2.getMeaning());
			len = meaning.length();
			const char* b = meaning.c_str();
			his_buff->text(b);
		}

		edit_meaning(his_out, nlen, len);
		
	}

	end();

}

void MainWindow::cb_his_del(Fl_Widget*, void* v) {

	((MainWindow*)v)->cb_his_del_i();

}

 // Xóa từ khỏi lịch sử tìm kiếm
void MainWindow::cb_his_del_i() {

	int index = history_db->value();
	if (index) {
		const char* keyWord = history_db->text(index);
		deleteWordFromHistoryFile(keyWord);
		history_db->clear();
		historyword = loadHistory(history_db);
		his_buff->text("");
	}

	end();

}

void MainWindow::cb_add_fav(Fl_Widget*, void*v) {

	((MainWindow*)v)->cb_add_fav_i();

}


// Thêm từ vào từ yêu thích
void MainWindow::cb_add_fav_i() {

	const char* keyWord = inp->value();
	string b = keyWord;
	_strlwr_s((char*)keyWord, b.length() + 1);
	word test1 = dictionary[keyWord];
	addWord test2 = dictionary_add[keyWord];

	if (keyWord[0] != '\0' && (!test1.isNull() || !test2.isNull())) {
		if (favoriteword[keyWord] < 1) {
			addWordToFavoriteFile(keyWord);
			favorite_db->clear();
			favoriteword = loadFavorite(favorite_db);
			fl_message(u8"Đã thêm vào từ yêu thích!");
		}
		else
			fl_message(u8"Từ đã được thêm vào!");
	}
	end();

}

void MainWindow::cb_fav_print(Fl_Widget*, void* v) {

	((MainWindow*)v)->cb_fav_print_i();

}

// Hiển thị nghĩa của từ yêu thích
void MainWindow::cb_fav_print_i() {

	fav_buff->text("");

	int index = favorite_db->value();
	const char* keyWord = favorite_db->text(index);
	string b = keyWord;
	int nlen = b.length();
	int len;

	word result = dictionary[keyWord];
	addWord result2 = dictionary_add[keyWord];

	if (!result.isNull() || !result2.isNull()) {
		if (!result.isNull()) {
			string meaning = getMeaning(result);
			len = meaning.length();
			const char* a = meaning.c_str();
			fav_buff->text(a);
		}
		else {
			string meaning = editAddMeaning(result2.getMeaning());
			len = meaning.length();
			const char* b = meaning.c_str();
			fav_buff->text(b);
		}

		edit_meaning(fav_out, nlen, len);
		
	}

	end();

}

void MainWindow::cb_fav_del(Fl_Widget*, void*v) {

	((MainWindow*)v)->cb_fav_del_i();

}

// Xóa từ khỏi danh mục yêu thích
void MainWindow::cb_fav_del_i() {

	int index = favorite_db->value();
	if (index) {
		const char* keyWord = favorite_db->text(index);
		deleteWordFromFavoriteFile(keyWord);
		favorite_db->clear();
		favoriteword = loadFavorite(favorite_db);
		fav_buff->text("");
	}

	end();

}