#ifndef SIMPLEWINDOW_H_INCLUDED
#define SIMPLEWINDOW_H_INCLUDED

#include <FL/Fl.H> 
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Hold_Browser.H>
#include <iostream>

class MainWindow : public Fl_Window {

	public:
		MainWindow(int w, int h, const char* title);
		~MainWindow();

	private:
		Fl_Box* title1;

		// Tab "Trang chủ"
		Fl_Button* translate;
		Fl_Button* quit;
		Fl_Input* inp;
		Fl_Text_Display* out;
		Fl_Text_Buffer* buff;
		Fl_Button* add_fav;

		// Tab "Thêm từ"
		Fl_Input* newWord;
		Fl_Input* type;
		Fl_Multiline_Input* newMeaning;
		Fl_Button* add;
		Fl_Button* cancel;
		Fl_Button* wdelete;
		Fl_Button* wchange;

		// Tab "Lịch sử"
		Fl_Text_Display* his_out;
		Fl_Text_Buffer* his_buff;
		Fl_Button* his_delete;

		// Tab "Từ yêu thích"
		Fl_Text_Display* fav_out;
		Fl_Text_Buffer* fav_buff;
		Fl_Button* fav_delete;

	private:
		static void cb_quit(Fl_Widget*, void*);
		inline void cb_quit_i();	// Thoát khỏi chương trình
		static void cb_print(Fl_Widget*, void*);
		inline void cb_print_i();	// In nghĩa của từ ra màn hình
		static void cb_db(Fl_Widget*, void*);
		inline void cb_db_i();	
		static void cb_add_fav(Fl_Widget*, void*);
		inline void cb_add_fav_i();	//Thêm từ vào mục yêu thích
		inline void edit_meaning(Fl_Text_Display* out, int nlen, int len); // Chỉnh sửa màu sắc cho nghĩa của từ
		
		static void cb_addword(Fl_Widget*, void*);
		inline void cb_addword_i();	// Thêm từ
		static void cb_cancel(Fl_Widget*, void*);
		inline void cb_cancel_i();	// Hủy thêm từ
		static void cb_adddb(Fl_Widget*, void*);
		inline void cb_adddb_i();
		static void cb_delete(Fl_Widget*, void*);
		inline void cb_delete_i();	// Xóa từ
		static void cb_change(Fl_Widget*, void*);
		inline void cb_change_i();	// Sửa từ

		static void cb_his_print(Fl_Widget*, void*);
		inline void cb_his_print_i();	// Hiển thị nghĩa của từ trong lịch sử tìm kiếm
		static void cb_his_del(Fl_Widget*, void*);
		inline void cb_his_del_i();	// Xóa từ khỏi lịch sử tìm kiếm

		static void cb_fav_print(Fl_Widget*, void*);
		inline void cb_fav_print_i();	// Hiển thị nghĩa của từ yêu thích
		static void cb_fav_del(Fl_Widget*, void*);
		inline void cb_fav_del_i();	// Xóa từ khỏi từ yêu thích
};

#endif // SIMPLEWINDOW_H_INCLUDED