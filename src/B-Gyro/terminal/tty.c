#include "terminal/terminal.h"
#include "klibc/memory.h"

void initTTY(uint8_t index) {
	_tty *tty = g_terminal.currentTTY;
	_node *ptr;

	tty->posX = 0;
	tty->posY = 0;

	tty->index = index;

	tty->textColor = DEFAULT_TEXT_COLOR;
	tty->backgroundColor = DEFAULT_BACKGROUND_COLOR;

	tty->buffer->first = &g_nodes[index][0];
	ptr = tty->buffer->first;
	for (uint8_t i = 0; i < (MAX_ROWS - 1); i++)
	{
		ptr->next = &g_nodes[index][i + 1];
		ptr = ptr->next;
	}
	ptr->next = tty->buffer->first;
	tty->buffer->last = tty->buffer->first;

	g_terminal.currentTTY->bufferSize = 1;
	// to do: call prompt ??
}

void clearTTY(uint32_t size) {

	bigBzero((uint16_t *)VIDEO_ADDRESS, size);

	g_terminal.currentTTY->posX = 0;
	g_terminal.currentTTY->posY = 0;
}

void putTtyBuffer(void) {
	_tty *tty;
	_node *line;

	tty = g_terminal.currentTTY;

	clearTTY(SCREEN_SIZE);

	line = tty->buffer->first;
	for (tty->posY = 0; tty->posY < g_terminal.currentTTY->bufferSize; tty->posY++) {
		for (tty->posX = 0; tty->posX < MAX_COLUMNS; tty->posX++) {
			if (line->buffer[tty->posX].character == '\0' || \
				line->buffer[tty->posX].character == '\n')
				break;
			putCellOnVga(line->buffer[tty->posX], tty->posX, tty->posY);
		}
		line = line->next;
	}
	tty->posY--;
	if (tty->posX >= (MAX_COLUMNS - 1)) {
		updatePositionX(tty);
		putTtyBuffer();
	}
	putCharPos(' ', tty->posX, tty->posY);
	setCursor(tty->posX, tty->posY);
}

void	switchTTY(uint8_t index) {
	_tty	*tty;

	if ((index >= MAX_TTYS) || (index == g_terminal.currentTTY->index))
		return ;
	g_terminal.currentTTY->textColor = g_currentTextColor;
	g_terminal.currentTTY->backgroundColor = g_currentBackGroundColor;

	tty = &g_terminal.ttys[index];
	g_terminal.currentTTY = tty;
	if (tty->index != index)
		initTTY (index);
	g_currentTextColor = tty->textColor;
	g_currentBackGroundColor = tty->backgroundColor;
	putTtyBuffer();
}
