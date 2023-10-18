//SCT211-0722/2021
//MAXWELL CHANZU

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

// Function to get the CPU usage in percentage
float get_cpu_usage() {
    FILE* fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("Error opening /proc/stat");
        exit(1);
    }

    char buf[256];
    fgets(buf, sizeof(buf), fp);
    fclose(fp);

    unsigned long user, nice, system, idle, iowait, irq, softirq;
    sscanf(buf, "cpu %lu %lu %lu %lu %lu %lu %lu", &user, &nice, &system, &idle, &iowait, &irq, &softirq);

    unsigned long total = user + nice + system + idle + iowait + irq + softirq;
    unsigned long usage = total - idle;

    return ((float)usage / total) * 100;
}

// Function to update the CPU usage graph
gboolean update_graph(GtkWidget* drawing_area) {
    static FILE* gnuplotPipe = NULL; 
    if (gnuplotPipe == NULL) {
        gnuplotPipe = popen("gnuplot -persist", "w");
        if (gnuplotPipe == NULL) {
            g_print("Error: Could not open a pipe to gnuplot.\n");
            exit(1);
        }
    }

    float cpu_usage = get_cpu_usage();
    
    fprintf(gnuplotPipe, "set title 'CPU Usage Over Time'\n");
    fprintf(gnuplotPipe, "set xlabel 'Time'\n");
    fprintf(gnuplotPipe, "set ylabel 'CPU Usage (%)'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "plot '-' with lines title 'CPU Usage'\n");
   	
    // Append data to the plot
    fprintf(gnuplotPipe, "0 %f\n", cpu_usage);
    
    // Keep the plot updating
    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);

    return TRUE; // Keep updating
}

int main(int argc, char* argv[]) {
    //create gtk window
    
    gtk_init(&argc, &argv);

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "CPU Usage Graph");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget* drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(update_graph), NULL);

    gtk_widget_show_all(window);

    g_timeout_add(1000, (GSourceFunc)update_graph, drawing_area); // Update every 1000ms (1 second)

    gtk_main();

    return 0;
}

