#!/usr/bin/env python
import sys

from ui_MyKeyboard   import Ui_MyKeyboard
from PyQt4.QtCore import *
from PyQt4.QtGui  import *

class MyKeyboard(QWidget, Ui_MyKeyboard):
    def __init__(self, parent = None):
        super(QWidget, self).__init__(parent)
        self.setupUi(self)

    def printBtn(self):
        for btn in self.children():
            if btn.inherits("QWidget"):
                attr = QString('<key x="%1" y="%2" width="%3" height="%4" text="%5" background="./pics/btn.png" keycode="10" />').arg(btn.x()).arg(btn.y()).arg(btn.width()).arg(btn.height()).arg(btn.text())
                print attr
                

def main():
    app = QApplication(sys.argv)
    app.setQuitOnLastWindowClosed(True)
    mykb = MyKeyboard()
    mykb.printBtn()
#    app.exec_()

if __name__ == '__main__':
    main()

