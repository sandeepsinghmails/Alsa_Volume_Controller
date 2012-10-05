/* 
 * Author: Sandeep Singh
 * Date  : Oct 4, 2012
 * 
 * Copyright 2012 Sandeep Singh (sandeepsinghmails@gmail.com)
 *
 * This file is part of Alsa Volume Controller.
 * Alsa Volume Controller is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Alsa Volume Controller is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Alsa Volume Controller. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>  
#include <gtk/gtk.h> 

#define MAXSIZE 500  

char Buffer[MAXSIZE];

void GetSystemVolume(void);

void IncreaseVolume(GtkWidget *widget, gpointer window_label)
{
	/* Now, actually increase the Sound Level by 1 */
	system("amixer --quiet set Master 1+");

	/* Get System Volume */
	GetSystemVolume();

	/* Print Buffer Contents in GTK Window */
  	gtk_label_set_text(GTK_LABEL(window_label), Buffer);
}

void DecreaseVolume(GtkWidget *widget, gpointer window_label)
{
	/* Now, actually decrease the Sound Level by 1 */
	system("amixer --quiet set Master 1-");

	/* Get System Volume */
	GetSystemVolume();

	/* Print Buffer Contents in GTK Window */
    gtk_label_set_text(GTK_LABEL(window_label), Buffer);
}

int main(int argc, char** argv) 
{
	GtkWidget *window_label;
  	GtkWidget *window;
  	GtkWidget *window_frame;
  	GtkWidget *increase_vol;
  	GtkWidget *decrease_vol;

	/* Initialize the GTK+ Library */
  	gtk_init(&argc, &argv);

  	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	/* Set Title for GTK Window */
  	gtk_window_set_title(GTK_WINDOW(window), "ALSA Volume Controller");

	/* Set Default Size of the GTK Window */
  	gtk_window_set_default_size(GTK_WINDOW(window), 460, 150);


  	window_frame = gtk_fixed_new();
  	gtk_container_add(GTK_CONTAINER(window), window_frame);

  	increase_vol = gtk_button_new_with_label("+");
  	gtk_widget_set_size_request(increase_vol, 80, 35);
  	gtk_fixed_put(GTK_FIXED(window_frame), increase_vol, 50, 20);

  	decrease_vol = gtk_button_new_with_label("-");
  	gtk_widget_set_size_request(decrease_vol, 80, 35);
  	gtk_fixed_put(GTK_FIXED(window_frame), decrease_vol, 50, 80);

    window_label = gtk_label_new("copyright@SandeepSingh"); 
  	gtk_fixed_put(GTK_FIXED(window_frame), window_label, 190, 58); 

  	gtk_widget_show_all(window);

  	g_signal_connect(window, "destroy",
    G_CALLBACK (gtk_main_quit), NULL);

  	g_signal_connect(increase_vol, "clicked", 
    G_CALLBACK(IncreaseVolume), window_label);

  	g_signal_connect(decrease_vol, "clicked", 
    G_CALLBACK(DecreaseVolume), window_label);

  	gtk_main();

  return 0;
}

void GetSystemVolume(void)
{
 	FILE *fptr;

	/* Open a Pipe for Reading */
  	fptr = popen("amixer get Master|grep Mono:", "r");
  	if (fptr == NULL) 
	{
    	printf("popen() Failed !\n");
  	}

  	/* Store the Output into the Buffer */
  	fgets(Buffer, sizeof(Buffer)-1, fptr);

  	/* Close the Pipe */
  	pclose(fptr);
}
