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


        self.key2_btn = QPushButton('Two')
        self.key2_btn.setMinimumHeight(self.key_btn_height)
        self.key2_btn.setMaximumWidth(self.key_btn_width)

        self.key3_btn = QPushButton('Three')
        self.key3_btn.setMinimumHeight(self.key_btn_height)
        self.key3_btn.setMaximumWidth(self.key_btn_width)

        self.key4_btn = QPushButton('Four')
        self.key4_btn.setMinimumHeight(self.key_btn_height)

        self.key5_btn = QPushButton('Five')
        self.key5_btn.setMinimumHeight(self.key_btn_height)

        self.key6_btn = QPushButton('Six')
        self.key6_btn.setMinimumHeight(self.key_btn_height)

        main_grid.addWidget(self.key1_btn, 1, 1)
        main_grid.addWidget(self.key2_btn, 1, 2)
        main_grid.addWidget(self.key3_btn, 1, 3)

        main_grid.addWidget(self.key4_btn, 2, 1)
        main_grid.addWidget(self.key5_btn, 2, 2)
        main_grid.addWidget(self.key6_btn, 2, 3)

        self.setLayout(main_grid)



if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = main_page()
    ex.show()
    sys.exit(app.exec_())
