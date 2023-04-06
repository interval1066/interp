#pragma once

/**
 * This is our interface to the command interpreter.
 * Commands need to be listed here.
 */
const char* commands[] = { "aaa", "access-lists", "amplifiers", "app", "arp",
                           "badl", "batch", "bert", "help", "motd", "prompt",
									"quit", "date", "list", "time", "?" };

/**
 * Command funtion prototypes can go here.
 */
int aaa(char*);
int alist(char*);
int amp(char*);
int app(char*);
int arp(char*);
int badl(char*);
int batch(char*);
int bert(char*);
int help(char*);
int motd(char*);
int prompt(char*);
int quit(char*);
int date(char*);
int list(char*);
int time(char*);

/**
 * Then must be entered into this table
 */
int (*table[])() = {
	 aaa, alist, amp, app, arp, badl, batch, bert, help, motd, prompt, quit, date, list, time
};
