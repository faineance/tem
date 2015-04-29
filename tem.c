#include <gtk/gtk.h>
#include <vte/vte.h>

#include "config.h"


static gboolean do_copy (VteTerminal *terminal)
{
	vte_terminal_copy_clipboard (terminal);
	return TRUE;
}

static gboolean do_paste (VteTerminal *terminal)
{
	vte_terminal_paste_clipboard (terminal);
	return TRUE;
}

static gboolean do_quit ()
{
	gtk_main_quit ();
	return TRUE;
}

static gboolean on_key_press(GtkWidget *window, GdkEventKey *event, gpointer user_data)
{
	if (event->type != GDK_KEY_PRESS)
		return FALSE;

	VteTerminal *terminal = VTE_TERMINAL (user_data);

	if (event->state & GDK_CONTROL_MASK)
	{
		if (event->state & GDK_SHIFT_MASK)
		{
			switch (event->keyval) 
			{
				case GDK_KEY_C:
					return do_copy(terminal);
				case GDK_KEY_V:
					return do_paste(terminal);
				case GDK_KEY_Q:
					return do_quit();
			}
		}
	}
	return FALSE;
	
}

int main(int argc, char **argv) {

	gtk_init(&argc, &argv);

	GtkWindow *window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
	VteTerminal *vte = VTE_TERMINAL(vte_terminal_new());
	gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(vte));


	g_signal_connect(window, "delete_event", G_CALLBACK(do_quit), NULL);

	g_signal_connect(G_OBJECT(window), "key-press-event", G_CALLBACK(on_key_press), vte);
	g_signal_connect(vte, "child-exited", G_CALLBACK(do_quit), NULL);

	char *shell[2] = {SHELL, NULL};
	vte_terminal_spawn_sync(vte, 0, NULL, shell, NULL, 0, NULL, NULL, NULL, NULL, NULL);
	gtk_widget_show_all(GTK_WIDGET(window));
	gtk_main();
	return 0;
}


