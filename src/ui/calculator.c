#include <stdio.h>
#include <gtk/gtk.h>
#include "../core/evaluator/evaluator.h"

GtkWidget *entry;
GtkEntryBuffer *buffer;

static void delete_entry(GtkWidget *widget, gpointer data) {
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    gtk_entry_buffer_delete_text(buffer, 0, -1);
}

static void calculate_result(GtkWidget *widget, gpointer data) {
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    const char *input = gtk_entry_buffer_get_text(buffer);
    struct evaluation_result result = evaluate(input);
    char result_string[32];

    if (result.status == EVALUATOR_SUCCESS) {
        snprintf(result_string, 32, "%0.f", result.value);
        gtk_entry_buffer_set_text(buffer, result_string, -1);
    } else {
        gtk_entry_buffer_set_text(buffer, "Something went wrong", -1);
    }
}

static void print_symbol(GtkWidget *widget, gpointer data) {
    const char *c = (const char *)data;
    buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    gtk_entry_buffer_insert_text(buffer, gtk_entry_buffer_get_length(buffer), c,
                                 1);
}

static void create_button(GtkGrid *grid, const char *label, int column, int row,
                          int width, int height) {
    GtkWidget *button;
    button = gtk_button_new_with_label(label);
    g_signal_connect(button, "clicked", G_CALLBACK(print_symbol),
                     (gpointer)label);
    gtk_grid_attach(GTK_GRID(grid), button, column, row, width, height);
}

static void create_result_button(GtkGrid *grid) {
    GtkWidget *button;
    button = gtk_button_new_with_label("=");
    g_signal_connect(button, "clicked", G_CALLBACK(calculate_result), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 5, 1, 1);
}

static void create_delete_button(GtkGrid *grid) {
    GtkWidget *button;
    button = gtk_button_new_from_icon_name("edit-delete");
    g_signal_connect(button, "clicked", G_CALLBACK(delete_entry), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 5, 1, 1);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;

    grid = gtk_grid_new();
    window = gtk_application_window_new(app);
    entry = gtk_entry_new();

    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_widget_set_sensitive(entry, FALSE);

    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);
    create_button(GTK_GRID(grid), "7", 0, 1, 1, 1);
    create_button(GTK_GRID(grid), "8", 1, 1, 1, 1);
    create_button(GTK_GRID(grid), "9", 2, 1, 1, 1);
    create_button(GTK_GRID(grid), "*", 3, 1, 1, 1);

    create_button(GTK_GRID(grid), "4", 0, 2, 1, 1);
    create_button(GTK_GRID(grid), "5", 1, 2, 1, 1);
    create_button(GTK_GRID(grid), "6", 2, 2, 1, 1);
    create_button(GTK_GRID(grid), "-", 3, 2, 1, 1);

    create_button(GTK_GRID(grid), "1", 0, 3, 1, 1);
    create_button(GTK_GRID(grid), "2", 1, 3, 1, 1);
    create_button(GTK_GRID(grid), "3", 2, 3, 1, 1);
    create_button(GTK_GRID(grid), "+", 3, 3, 1, 1);

    create_button(GTK_GRID(grid), "0", 0, 4, 2, 1);
    create_button(GTK_GRID(grid), ".", 2, 4, 1, 1);
    create_button(GTK_GRID(grid), "/", 3, 4, 1, 1);

    create_button(GTK_GRID(grid), "(", 0, 5, 1, 1);
    create_button(GTK_GRID(grid), ")", 1, 5, 1, 1);
    create_result_button(GTK_GRID(grid));
    create_delete_button(GTK_GRID(grid));

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("calculator.gtk", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}