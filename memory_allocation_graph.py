import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget, QPushButton, QLabel, QTextEdit
from PyQt5.QtGui import QPainter, QColor, QFont
from PyQt5.QtCore import Qt

class MemoryBlock:
    def __init__(self, size, color):
        self.size = size
        self.color = color

class MemoryManagerGUI(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Memory Manager GUI")
        self.setGeometry(100, 100, 800, 600)

        self.blocks = [
            MemoryBlock(100, QColor(0, 0, 255)),  # Blue
            MemoryBlock(80, QColor(255, 0, 0)),   # Red
            MemoryBlock(120, QColor(0, 255, 0)),  # Green
            MemoryBlock(90, QColor(255, 255, 0)),# Yellow
            MemoryBlock(110, QColor(255, 0, 255))# Magenta
            # Add more initial memory blocks if needed
        ]

        self.label = QLabel("Memory Blocks:", self)
        self.text_edit = QTextEdit(self)

        self.create_page_family_button = QPushButton("Create Page Family", self)
        self.create_page_family_button.clicked.connect(self.create_page_family)
        self.allocate_memory_button = QPushButton("Allocate Memory", self)
        self.allocate_memory_button.clicked.connect(self.allocate_memory)
        self.free_memory_button = QPushButton("Free Memory", self)
        self.free_memory_button.clicked.connect(self.free_memory)

        layout = QVBoxLayout()
        layout.addWidget(self.label)
        layout.addWidget(self.text_edit)
        layout.addWidget(self.create_page_family_button)
        layout.addWidget(self.allocate_memory_button)
        layout.addWidget(self.free_memory_button)

        layout.addStretch(1)

        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)
        font = QFont("Arial", 10)
        painter.setFont(font)

        x = 50
        y = 200
        height = 50
        spacing = 10

        for block in self.blocks:
            painter.setBrush(block.color)
            painter.drawRect(x, y, block.size, height)
            painter.drawText(x, y - 20, f"Size: {block.size}")
            x += block.size + spacing

    def create_page_family(self):
        # Add code to create a new page family
        # For demo purposes, let's add a new block with random size and color
        new_block = MemoryBlock(80, QColor(0, 0, 0))  # Black
        self.blocks.append(new_block)
        self.update()

    def allocate_memory(self):
        # Add code to simulate memory allocation
        # For demo purposes, let's increase the size of the first block
        if self.blocks[0].size < 200:
            self.blocks[0].size += 20
            self.update()

    def free_memory(self):
        # Add code to simulate freeing memory
        # For demo purposes, let's remove the last block
        if self.blocks:
            self.blocks.pop()
            self.update()

        # Save memory usage summary and block usage information to a text file
        with open("memory_usage_output.txt", "w") as file:
            file.write("Memory Usage Summary:\n")
            # Add memory usage summary here
            file.write("\nBlock Usage:\n")
            # Add block usage information here
            self.text_edit.setText("Memory usage summary and block usage information have been saved to memory_usage_output.txt")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    gui = MemoryManagerGUI()
    gui.show()
    sys.exit(app.exec_())
