#include <iostream>
#include <vector>
#include <cstring>
#include <gtk/gtk.h>

//********************************//
//                                //
//      Example position widget   //
//      on window table.          //
//                                //
//           0        1           //
//      *--------**--------*      //
//      | button || check  |      //
//  0   |  0,0   ||  0,1   |      //
//      *--------**--------*      //
//      *--------**--------*      //
//      | input  || slider |      //
//  1   |  1,0   ||  1,1   |      //
//      *--------**--------*      //
//      *--------**--------*      //
//      | list   ||  etc   |      //
//  2   |  2,0   ||  2,1   |      //
//      *--------**--------*      //
//                                //
//********************************//

using namespace std;

namespace UIGpio 
{
	struct _DescEvent
	{
		string name;
		string type;
		string value;
	}
	DescEvent;

	class UI 
	{
		public:
		GtkWidget *window;
		GdkPixbuf *icon;
		GtkWidget *zone;

		GtkWidget *toggle;
		GtkWidget *button;
		GtkWidget *check;
		GtkWidget *slider;
		GtkWidget *label_slider;
		GtkWidget *hbox_slider;
		GtkWidget *image;
		GtkWidget *input;
		GtkWidget *label_input;
		GtkWidget *hbox_input;
		GtkWidget *list;
		GtkWidget *label_list;
		GtkWidget *vbox_list;
		GtkWidget *btn_image;
		GtkWidget *btn_button;
		GtkWidget *menubar;
		GtkWidget *filemenu;

	        GtkWidget *color_palett;
		int width_window;
		int height_window;

		static _DescEvent buffer;
		_DescEvent getEvent() { return buffer; }

		GdkPixbuf *create_pixbuf(const gchar * filename) 
		{
			GdkPixbuf *pixbuf;
		   	GError *error = NULL;
		   	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
		   	if (!pixbuf) {
		       		fprintf(stderr, "%s\n", error->message);
		      		g_error_free(error);
		   	}
		   	return pixbuf;
		}

		static void clb_button(GtkWidget *widget, gpointer data)
		{ 
			static bool valued = false;
			const gchar * n	= gtk_button_get_label(GTK_BUTTON(widget));
			buffer.name = n;
			buffer.type = "Button";
			valued =! valued;
			buffer.value= (valued)?"1":"0";
		}

		static void clb_imgbutton(GtkWidget *widget, gpointer str)
		{ 
			static bool valued = false;
			//const gchar * n = gtk_button_get_label(GTK_BUTTON(widget));
			buffer.name = "";//n;
			buffer.type = "ImageButton";
			valued =! valued;
			buffer.value= (valued)?"1":"0";
		}

		static void clb_toggle(GtkWidget *widget, gpointer data)
		{ 
			static bool valued = false;
			const gchar * n	= gtk_button_get_label(GTK_BUTTON(widget));
			buffer.name = n;
			buffer.type = "Toggle";
			valued =! valued;
			buffer.value= (valued)?"1":"0";
		}

		static void clb_check(GtkWidget *widget, gpointer data)
		{
			static bool valued = false;
			const gchar * n	= gtk_button_get_label(GTK_BUTTON(widget));		
			buffer.name = n;
			buffer.type = "Check";
			valued =! valued;
			buffer.value= (valued)?"1":"0";
		}

		static void clb_slider(GtkRange *range, gpointer data)
		{ 
			gdouble val  = gtk_range_get_value(range);
			const gchar * n = gtk_label_get_text(GTK_LABEL(data));
			buffer.name = (char *)n;
			buffer.type = "Slider";
			buffer.value= to_string(val);
		}

		static void clb_input(GtkWidget *widget, gpointer data)
		{ 
			const gchar *text = gtk_entry_get_text (GTK_ENTRY(widget));
			const gchar * n = gtk_label_get_text(GTK_LABEL(data));
			buffer.name = (char *)n;
			buffer.type = "Input";
			buffer.value= text;
		}

		static void clb_list(GtkComboBox *combo, gpointer data)
		{ 
			const gchar *text = gtk_combo_box_get_active_text(combo);
			const gchar * n = gtk_label_get_text(GTK_LABEL(data));
			buffer.name = (char *)n;
			buffer.type = "List";
			buffer.value= text;
		}

		static gint delete_event(GtkWidget *widget, gpointer data) { exit(0); return TRUE; }
		static void destroy(GtkWidget *widget, gpointer data) { gtk_main_quit(); }

		void setWindowSize(int w, int h)
		{
			width_window = w;
			height_window = h;
		}

		void setup(string title="title", int colum=10, int rows=10, string _icon="")
		{	
			int argc = 0;
			char ** argv;
			gtk_init(&argc, &argv);

			window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
			gtk_container_border_width (GTK_CONTAINER (window), 2);

			gtk_window_set_default_size(GTK_WINDOW(window),width_window,height_window);
			gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
			gtk_window_set_title(GTK_WINDOW(window), title.c_str());
			if(_icon!="") {
				const gchar* ic = (const gchar *)_icon.c_str();
				icon = create_pixbuf(ic);  
				gtk_window_set_icon(GTK_WINDOW(window), icon);
			}

			gtk_signal_connect (GTK_OBJECT (window), "delete_event", GTK_SIGNAL_FUNC (delete_event), NULL);
			gtk_signal_connect (GTK_OBJECT (window), "destroy", GTK_SIGNAL_FUNC (destroy), NULL);

			zone = gtk_table_new(colum,rows,TRUE);
			gtk_table_set_row_spacing(GTK_TABLE(zone), 1, 1);
			gtk_table_set_col_spacing(GTK_TABLE(zone), 1, 1);

			gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(zone));
		}

		void addColorPalett(string title)
		{
			//bug
			color_palett = gtk_color_selection_dialog_new(title.c_str());
		        //GtkResponseType result = (GtkResponseType)
			gtk_dialog_run(GTK_DIALOG(color_palett));
			/*if (result == GTK_RESPONSE_OK) {
				GdkColor color;
				GtkColorSelection *colorsel;

				colorsel = GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG(color_palett)->colorsel);
				gtk_color_selection_get_current_color(colorsel, &color);
				//gtk_widget_modify_fg(GTK_WIDGET(label), GTK_STATE_NORMAL, &color);

			}*/
			// not complete	
		}

		void addList(string title, vector<string> listed, int column, int row)
		{
			label_list = gtk_label_new(title.c_str());
			list = gtk_combo_box_new_text();
			for(auto & l : listed) {
				gtk_combo_box_append_text(GTK_COMBO_BOX(list), l.c_str());
			}
			vbox_list = gtk_vbox_new(FALSE, 0);
			gtk_box_pack_start(GTK_BOX(vbox_list), label_list, TRUE, FALSE, 0);
			gtk_box_pack_start(GTK_BOX(vbox_list), list,       TRUE, FALSE, 0);

			gtk_table_attach(GTK_TABLE(zone), vbox_list, column, column+1, row, row + 1, (GtkAttachOptions) (GTK_FILL | GTK_EXPAND),
												(GtkAttachOptions) (GTK_FILL | GTK_EXPAND), 0, 0);
			g_signal_connect(G_OBJECT(list), "changed", G_CALLBACK(clb_list), label_list);
		}

		void addInput(string title, int column, int row)
		{
			label_input = gtk_label_new(title.c_str());
			input = gtk_entry_new();
			
			hbox_input = gtk_vbox_new(FALSE, 0);
			gtk_box_pack_start(GTK_BOX(hbox_input), label_input, TRUE, FALSE, 0);
			gtk_box_pack_start(GTK_BOX(hbox_input), input,       TRUE, FALSE, 0);
			gtk_table_attach(GTK_TABLE(zone), hbox_input, column, column+1, row, row + 1, (GtkAttachOptions) (GTK_FILL | GTK_EXPAND),
												      (GtkAttachOptions) (GTK_FILL | GTK_EXPAND), 0, 0);
			g_signal_connect(input, "activate", G_CALLBACK(clb_input), label_input);
		}

		void addImage(string img, int column, int row)
		{
			image = gtk_image_new_from_file(img.c_str());
			gtk_table_attach(GTK_TABLE(zone), image, column, column+1, row, row + 1, (GtkAttachOptions) (GTK_FILL | GTK_EXPAND),
												 (GtkAttachOptions) (GTK_FILL | GTK_EXPAND), 0, 0);
		}

		void addSlider(string title, int column, int row, int min, int max, int step=1)
		{
			slider = gtk_hscale_new_with_range(min,max,step);
			label_slider = gtk_label_new(title.c_str());

			hbox_slider = gtk_vbox_new(FALSE, 0);
			gtk_box_pack_start(GTK_BOX(hbox_slider), label_slider, TRUE, TRUE, 0);
			gtk_box_pack_start(GTK_BOX(hbox_slider), slider,       TRUE, TRUE, 0);

			gtk_table_attach(GTK_TABLE(zone), hbox_slider, column, column+1, row, row + 1, (GtkAttachOptions) (GTK_FILL | GTK_EXPAND),
												       (GtkAttachOptions) (GTK_FILL | GTK_EXPAND), 0, 0);
			g_signal_connect(slider, "value-changed", G_CALLBACK(clb_slider), label_slider);
		}

		void addToggle(string title, int column, int row)
		{
			toggle = gtk_toggle_button_new_with_mnemonic(title.c_str());
			gtk_signal_connect(GTK_OBJECT (toggle), "clicked", GTK_SIGNAL_FUNC (clb_toggle), NULL);
			gtk_table_attach(GTK_TABLE(zone), toggle, column, column+1, row, row + 1, (GtkAttachOptions) (GTK_FILL | GTK_EXPAND),
												  (GtkAttachOptions) (GTK_FILL | GTK_EXPAND), 0, 0);
		}

		void addCheck(string title, int column, int row)
		{
			check = gtk_check_button_new_with_label(title.c_str());
			gtk_signal_connect(GTK_OBJECT (check), "clicked", GTK_SIGNAL_FUNC (clb_check), NULL);
			gtk_table_attach(GTK_TABLE(zone), check, column, column+1, row, row + 1,  (GtkAttachOptions) (GTK_FILL | GTK_EXPAND),
												  (GtkAttachOptions) (GTK_FILL | GTK_EXPAND), 0, 0);
		}

		void addButton(string title, int column, int row)
		{
			button = gtk_button_new_with_label(title.c_str());
			gtk_widget_set_size_request(button,10,5);
			gtk_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(clb_button), NULL);
			gtk_table_attach(GTK_TABLE(zone), button, column, column+1, row, row + 1, (GtkAttachOptions) (GTK_FILL | GTK_EXPAND),
												  (GtkAttachOptions) (GTK_FILL | GTK_EXPAND), 0, 0);
		}
		
		void addButtonImage(const gchar * title, string path, int column, int row)
		{
			//bug get name
			btn_image = gtk_image_new_from_file(path.c_str());
			btn_button = gtk_button_new();//_with_label(title.c_str());
			gtk_button_set_image(GTK_BUTTON(btn_button), btn_image);
			gtk_signal_connect(GTK_OBJECT(btn_button), "clicked", GTK_SIGNAL_FUNC(clb_imgbutton), NULL);
			gtk_table_attach(GTK_TABLE(zone), btn_button, column, column+1, row, row + 1, (GtkAttachOptions) (GTK_FILL | GTK_EXPAND),
												      (GtkAttachOptions) (GTK_FILL | GTK_EXPAND), 0, 0);
		}
		
		void show() 
		{
			gtk_widget_show_all(window);
			gtk_main();
		}
	};
	_DescEvent UI::buffer;
};
