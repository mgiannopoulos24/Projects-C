#include <gtk/gtk.h>
#include "sudoku.h"

#define GRID_PADDING_PERCENT 0.15
#define BUTTON_WIDTH_CHARS 10

int grid[N][N];
GtkWidget *entry_grid[N][N];

void load_sudoku(GtkWidget *widget, gpointer data) {
    readGrid(grid, "sudoku.txt");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char buffer[2];
            snprintf(buffer, sizeof(buffer), "%d", grid[i][j]);
            gtk_entry_set_text(GTK_ENTRY(entry_grid[i][j]), buffer[0] == '0' ? "" : buffer);
        }
    }
}

void solve_sudoku(GtkWidget *widget, gpointer data) {
    if (solveSudoku(grid)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                char buffer[2];
                snprintf(buffer, sizeof(buffer), "%d", grid[i][j]);
                gtk_entry_set_text(GTK_ENTRY(entry_grid[i][j]), buffer);
            }
        }
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
                                                   "No solution exists");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *main_grid;
    GtkWidget *grid_container;
    GtkWidget *load_button;
    GtkWidget *solve_button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Sudoku Solver");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 450);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    main_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), main_grid);

    grid_container = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_container), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid_container), TRUE);
    gtk_widget_set_margin_top(grid_container, 20);
    gtk_widget_set_margin_bottom(grid_container, 20);
    gtk_widget_set_margin_start(grid_container, 75);
    gtk_widget_set_margin_end(grid_container, 20);
    gtk_grid_attach(GTK_GRID(main_grid), grid_container, 0, 0, 1, 1);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            GtkWidget *frame = gtk_frame_new(NULL);
            gtk_grid_attach(GTK_GRID(grid_container), frame, j, i, 1, 1);
            GtkWidget *sub_grid = gtk_grid_new();
            gtk_grid_set_column_homogeneous(GTK_GRID(sub_grid), TRUE);
            gtk_grid_set_row_homogeneous(GTK_GRID(sub_grid), TRUE);
            gtk_container_add(GTK_CONTAINER(frame), sub_grid);

            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    int row = i * 3 + k;
                    int col = j * 3 + l;
                    entry_grid[row][col] = gtk_entry_new();
                    gtk_entry_set_max_length(GTK_ENTRY(entry_grid[row][col]), 1);
                    gtk_entry_set_width_chars(GTK_ENTRY(entry_grid[row][col]), 1);
                    gtk_grid_attach(GTK_GRID(sub_grid), entry_grid[row][col], l, k, 1, 1);
                }
            }
        }
    }


    // Calculate padding in pixels based on percentage of window width
    gint window_width;
    gtk_window_get_size(GTK_WINDOW(window), &window_width, NULL);
    gint padding_pixels = window_width * GRID_PADDING_PERCENT;


    load_button = gtk_button_new_with_label("Load Sudoku");
    g_object_set(load_button, "width-request", padding_pixels / 4, NULL);  // Set button width
    g_signal_connect(load_button, "clicked", G_CALLBACK(load_sudoku), NULL);
    gtk_widget_set_margin_start(load_button, padding_pixels);
    gtk_grid_attach(GTK_GRID(main_grid), load_button, 0, 1, 1, 1);

    solve_button = gtk_button_new_with_label("Solve Sudoku");
    g_object_set(load_button, "width-request", padding_pixels / 4, NULL);  // Set button width
    g_signal_connect(solve_button, "clicked", G_CALLBACK(solve_sudoku), NULL);
    gtk_widget_set_margin_top(solve_button, 20);
    gtk_widget_set_margin_start(solve_button, padding_pixels);
    gtk_grid_attach(GTK_GRID(main_grid), solve_button, 0, 2, 1, 1);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.sudoku", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
