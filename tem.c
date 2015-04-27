#include <gtk/gtk.h>
#include <vte/vte.h>

#include "config.h"


int main(int argc, char **argv) {
	gtk_init(&argc, &argv);

	GtkWindow *window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
	VteTerminal *vte = VTE_TERMINAL(vte_terminal_new());
	gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(vte));


	g_signal_connect(window, "delete_event", gtk_main_quit, NULL);

	g_signal_connect(vte, "child-exited", gtk_main_quit, NULL);

	char *shell[2] = {SHELL, NULL};
	vte_terminal_spawn_sync(vte, 0, NULL, shell, NULL, 0, NULL, NULL, NULL, NULL, NULL);
	gtk_widget_show_all(GTK_WIDGET(window));
	gtk_main();
	return 0;
}


