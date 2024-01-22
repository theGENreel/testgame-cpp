#include "overlays/BaseOverlay.h"
#include <curses.h>
#include <iostream>
#include <string>

BaseOverlay::BaseOverlay(float size_multiplier) {
  this->size_multiplier = size_multiplier;
  getmaxyx(stdscr, this->screen_height, this->screen_width); 
  this->window = newwin((int)this->screen_height * this->size_multiplier, (int)this->screen_width * this->size_multiplier, (int)this->screen_height * ((1 - this->size_multiplier) / 2), (int)this->screen_width * ((1 - this->size_multiplier) / 2));
}

WINDOW* BaseOverlay::GetWindow() {
  return this->window;
}

int BaseOverlay::GetScreenWidth() {
  return this->screen_width;
}

int BaseOverlay::GetScreenHeight() {
  return this->screen_height;
}

int BaseOverlay::GetWindowWidth() {
  return getmaxx(this->window);
}

int BaseOverlay::GetWindowHeight() {
  return getmaxy(this->window);
}

bool BaseOverlay::IsExiting() {
  return this->exiting;
}

void BaseOverlay::Draw() {

}

void BaseOverlay::Input(int key) {

}

std::string BaseOverlay::StringInMid(std::string str) {
  std::string res = std::string("");
  for (int i = 0; i<(int)(((this->GetWindowWidth() - 2) - (str.length())) / 2); i++)
    res += " ";
  res += str;
  std::string helper = std::string("");
  for (int i = 0; i<this->GetWindowWidth() - 2 - res.length(); i++)
    helper += " ";
  res += helper;
  return res;
}
