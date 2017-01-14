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

        main_grid = QGridLayout()

        # Layout Keyboard button buttons

        self.key1_btn = QPushButton('1')
        self.key1_btn.clicked.connect(lambda: self.key_clicked(1))

        self.key2_btn = QPushButton('2')
        self.key2_btn.clicked.connect(lambda: self.key_clicked(2))

        self.key3_btn = QPushButton('3')
        self.key3_btn.clicked.connect(lambda: self.key_clicked(3))

        self.key4_btn = QPushButton('4')
        self.key4_btn.clicked.connect(lambda: self.key_clicked(4))

        self.key5_btn = QPushButton('5')
        self.key5_btn.clicked.connect(lambda: self.key_clicked(5))

        self.key6_btn = QPushButton('6')
        self.key6_btn.clicked.connect(lambda: self.key_clicked(6))

        main_grid.addWidget(self.key1_btn, 1, 1)
        main_grid.addWidget(self.key2_btn, 1, 2)
        main_grid.addWidget(self.key3_btn, 1, 3)

        main_grid.addWidget(self.key4_btn, 2, 1)
        main_grid.addWidget(self.key5_btn, 2, 2)
        main_grid.addWidget(self.key6_btn, 2, 3)

        self.key_list = [self.key1_btn, self.key2_btn, self.key3_btn, self.key4_btn, self.key5_btn, self.key6_btn]

        for i in range(6): # Iteratively set the width and height of keys
            self.key_list[i].setMinimumHeight(self.key_btn_height)
            self.key_list[i].setMaximumWidth(self.key_btn_width)

        # Layout additional UI Features

        self.macro_string = QLabel('-- No Current Macro -- Click a key button to alter --')
        # TODO alter string with macro key string for each button pressed

        self.save_btn = QPushButton('Save config')
        self.save_btn.setMaximumWidth(self.key_btn_width)
        self.save_btn.clicked.connect(lambda: self.macro_string.setText('akdkdk'))

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

        # Tooltips
        self.macro_string.setToolTip('Displays macro set to key selected, if applicable')
        self.save_btn.setToolTip('Writes out current macro setting to a file')
        self.load_btn.setToolTip('Load previous macro settings from a file')
        self.start_macro_btn.setToolTip('Begin recording all key strokes')
        self.stop_macro_btn.setToolTip('Stop recording all key strokes')
        self.flash_btn.setToolTip('Write macros to Teensy')

        # Name all buttons as themselves for css styling
        self.flash_btn.setObjectName('flash_btn')
        self.key1_btn.setObjectName('key_btn_generic')
        self.key2_btn.setObjectName('key_btn_generic')
        self.key3_btn.setObjectName('key_btn_generic')
        self.key4_btn.setObjectName('key_btn_generic')
        self.key5_btn.setObjectName('key_btn_generic')
        self.key6_btn.setObjectName('key_btn_generic')
        self.load_btn.setObjectName('work_btn_generic')
        self.save_btn.setObjectName('work_btn_generic')
        self.start_macro_btn.setObjectName('work_btn_generic')
        self.stop_macro_btn.setObjectName('work_btn_generic')
        self.macro_string.setObjectName('macro_string')
        self.setObjectName('main_grid')

        # Load in css stylesheet from file
        style_file = 'python_gui_styling.css'
        with open(style_file, 'r') as fh:
            self.setStyleSheet(fh.read())

        self.setLayout(main_grid)
        self.show()

    def save_config(self):
        print 'Save Config Now'

    def load_config(self):
        print 'Load Config Now'

    def start_macro(self):
        print 'Start Recording Macro'
        #TODO keep focus on key button once completed

    def stop_macro(self):
        print 'Stop Recording Macro'

    def flash(self):
        print 'Program Keyboard Now'

    def key_clicked(self, key_number):
        print 'Pressed button {0}'.format(key_number)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = main_page()
    ex.show()
    sys.exit(app.exec_())
