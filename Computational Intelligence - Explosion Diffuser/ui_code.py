import os
import pygubu
import tkinter as tk
import tkinter.ttk as ttk
import psutil  # multi-platform library for system resource usage tracking


PROJECT_PATH = os.path.dirname(__file__)
PROJECT_UI = os.path.join(PROJECT_PATH, "ui.ui")


class UiApp:
    def __init__(self):
        self.builder = builder = pygubu.Builder()
        builder.add_resource_path(PROJECT_PATH)
        builder.add_from_file(PROJECT_UI)
        self.mainwindow = builder.get_object('mainwindow')
        builder.connect_callbacks(self)
        
        #root.tk.call locates the theme package and selects styles we wish #to use from that package
        self.mainwindow.tk.call('lappend', 'auto_path', '/home/dimitrije/Desktop/Computational Intelligence - Explosion Diffuser/awthemes-10.2.1')
        self.mainwindow.tk.call('package', 'require', 'awdark')
        self.mainwindow.tk.call('package', 'require', 'awlight')
        #to change the style we need to create an instance of 'Style' class
        self.style = ttk.Style(self.mainwindow)
        self.style.theme_use('awdark')
        #self.style.theme_use('awlight')
        self.show_resource_usage()

    
    def brute_force_command(self):
        pass

    def monte_carlo_command(self):
        pass

    def genetic_algorithm_command(self):
        pass

    def generate_problem_command(self):
        pass

    def random_problem_validate_callback(self):
        pass

    def current_best_solution_validate_callback(self):
        pass

    def start_callback(self):
        pass

    def change_theme_callback(self):
        if self.style.theme_use() == 'awdark':
            self.style.theme_use('awlight')
        else:
            self.style.theme_use('awdark')

    def get_size_input(self):
        return self.builder.get_variable('input_size').get()

    def show_resource_usage(self):
        self.builder.get_variable('cpu_usage').set(psutil.cpu_percent())
        self.builder.get_variable('memory_usage').set(psutil.virtual_memory().percent)
        self.mainwindow.after(1000, self.show_resource_usage) #updates stat every 1000ms
	#psutil.virtual_memory().percent

    def run(self):
        self.mainwindow.mainloop()
