import os
import sys
from PySide.QtCore import *
from PySide.QtGui import *


class main_page(QWidget):
    min_width = 500
    min_height = 340
    key_btn_height = min_height / 4
    key_btn_width = min_width / 5

    def __init__(self):
        super(main_page, self).__init__()

        self.setGeometry(600, 300, self.min_width, self.min_height)
        self.setWindowTitle('Macro Keyboard Configurator (J.Sanson and P.Savill)')
        self.setMinimumSize(self.min_width, self.min_height)
        self.setMaximumSize(self.min_width, self.min_height)

        main_widget = QWidget()
        main_grid = QGridLayout()

        # Add a graphical selection of keyboard key
        # -----------------------
        #   1   |   2    |   3
        # -----------------------
        #   4   |   5    |   6
        # -----------------------


        self.key1_btn = QPushButton('One')
        self.key1_btn.setMinimumHeight(self.key_btn_height)
        self.key1_btn.setMaximumWidth(self.key_btn_width)
        self.key1_btn.clicked.connect(self.key1_clicked)

        self.key2_btn = QPushButton('Two')
        self.key2_btn.setMinimumHeight(self.key_btn_height)
        self.key2_btn.setMaximumWidth(self.key_btn_width)
        self.key2_btn.clicked.connect(self.key2_clicked)

        self.key3_btn = QPushButton('Three')
        self.key3_btn.setMinimumHeight(self.key_btn_height)
        self.key3_btn.setMaximumWidth(self.key_btn_width)
        self.key3_btn.clicked.connect(self.key3_clicked)

        self.key4_btn = QPushButton('Four')
        self.key4_btn.setMinimumHeight(self.key_btn_height)
        self.key4_btn.setMaximumWidth(self.key_btn_width)
        self.key4_btn.clicked.connect(self.key4_clicked)

        self.key5_btn = QPushButton('Five')
        self.key5_btn.setMinimumHeight(self.key_btn_height)
        self.key5_btn.setMaximumWidth(self.key_btn_width)
        self.key5_btn.clicked.connect(self.key5_clicked)

        self.key6_btn = QPushButton('Six')
        self.key6_btn.setMinimumHeight(self.key_btn_height)
        self.key6_btn.setMaximumWidth(self.key_btn_width)
        self.key6_btn.clicked.connect(self.key6_clicked)

        main_grid.addWidget(self.key1_btn, 1, 1)
        main_grid.addWidget(self.key2_btn, 1, 2)
        main_grid.addWidget(self.key3_btn, 1, 3)

        main_grid.addWidget(self.key4_btn, 2, 1)
        main_grid.addWidget(self.key5_btn, 2, 2)
        main_grid.addWidget(self.key6_btn, 2, 3)

        self.macro_string = QLabel('\t\t-- No Current Macro -- Click a key button to alter --')
        # TODO alter string with macro key string for each button pressed

        self.save_btn = QPushButton('Save config')
        self.save_btn.setMaximumWidth(self.key_btn_width)
        self.save_btn.clicked.connect(self.save_config)

        self.start_macro_btn = QPushButton('Start Record')
        self.start_macro_btn.setMaximumWidth(self.key_btn_width)

        self.stop_macro_btn = QPushButton('Stop Record')
        self.stop_macro_btn.setMaximumWidth(self.key_btn_width)

        self.load_btn = QPushButton('Load Config')
        self.load_btn.setMaximumWidth(self.key_btn_width)

        self.flash_btn = QPushButton('FLASH')


        main_grid.addWidget(self.macro_string, 3, 1, 1, 3)

        main_grid.addWidget(self.save_btn, 4, 1)
        main_grid.addWidget(self.load_btn, 5, 1)

        main_grid.addWidget(self.start_macro_btn, 4, 2)
        main_grid.addWidget(self.stop_macro_btn, 5, 2)

        main_grid.addWidget(self.flash_btn, 5, 3)

        self.setLayout(main_grid)

    def save_config(self):
        print 'Save Config Now'

    def load_config(self):
        print 'Load Config Now'

    def start_macro(self):
        print 'Start Recording Macro'

    def stop_macro(self):
        print 'Stop Recording Macro'

    def flash(self):
        print 'Program Keyboard Now'

    def key1_clicked(self):
        print 'You clicked a key, yay'

    def key2_clicked(self):
        print 'You clicked a key, yay'

    def key3_clicked(self):
        print 'You clicked a key, yay'

    def key4_clicked(self):
        print 'You clicked a key, yay'

    def key5_clicked(self):
        print 'You clicked a key, yay'

    def key6_clicked(self):
        print 'You clicked a key, yay'


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = main_page()
    ex.show()
    sys.exit(app.exec_())
