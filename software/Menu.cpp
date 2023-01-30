// ----------------------------------------------------------------------------
// MicroMenu
// Copyright (c) 2014 karl@pitrich.com
// All rights reserved.
// License: MIT
// ----------------------------------------------------------------------------

#include <Arduino.h>
#include "Menu.h"

// ----------------------------------------------------------------------------

namespace Menu {

// ----------------------------------------------------------------------------

Item_t NullItem PROGMEM = { (const Menu::Item_s *)NULL, (const Menu::Item_s *)NULL, (const Menu::Item_s *)NULL, (const Menu::Item_s *)NULL, (const Menu::Callback_t)NULL, (const char *)NULL };

// ----------------------------------------------------------------------------

Engine::Engine() 
  : currentItem(&Menu::NullItem)
{
}

Engine::Engine(const Item_t *initialItem) 
  : currentItem(initialItem)
{
}

// ----------------------------------------------------------------------------

const char * Engine::getLabel(const Item_t * item) const {
  return (const char *)pgm_read_ptr((item == NULL) ? &currentItem->Label : &item->Label);
}

const Item_t * Engine::getPrev(const Item_t * item) const {
  return (const Item_t *)pgm_read_ptr((item == NULL) ? &currentItem->Previous : &item->Previous);
}

const Item_t * Engine::getNext(const Item_t * item) const {
  return (const Item_t *)pgm_read_ptr((item == NULL) ? &currentItem->Next : &item->Next);
}

const Item_t * Engine::getParent(const Item_t * item) const {
  return (const Item_t *)pgm_read_ptr((item == NULL) ? &currentItem->Parent : &item->Parent);
}

const Item_t * Engine::getChild(const Item_t * item) const {
  return (const Item_t *)pgm_read_ptr((item == NULL) ? &currentItem->Child : &item->Child);
}

// ----------------------------------------------------------------------------

void Engine::navigate(const Item_t * targetItem) {
  uint8_t commit = true;
  if (targetItem && targetItem != &Menu::NullItem) {
    if (targetItem == getParent(currentItem)) { // navigating back to parent
      commit = executeCallbackAction(actionParent); // exit/save callback
    }
    if (commit) {
      currentItem = targetItem;
      executeCallbackAction(actionLabel);
    }
  }
}

// ----------------------------------------------------------------------------

void Engine::invoke(void) {
  const Item_t *child = getChild();
  executeCallbackAction(actionTrigger);
  if (child && child != &Menu::NullItem) { // navigate to registered submenuitem
    navigate(child);
  }
}

// ----------------------------------------------------------------------------

bool Engine::executeCallbackAction(const Action_t action) const {
  if (currentItem && currentItem != NULL) {
    Callback_t callback = (Callback_t)pgm_read_ptr(&currentItem->Callback);

    if (callback != NULL) {
      return (*callback)(action);
    }
  }
  return true;
}

// ----------------------------------------------------------------------------

Info_t Engine::getItemInfo(const Item_t * item) const {
  Info_t result = { 0, 0 };
  const Item_t * i = getChild(getParent());
  for (; i && i != &Menu::NullItem; i = getNext(i)) {
    if (i == item) {
      result.position = result.siblings;
    }
    result.siblings++;
  }

  return result;
}

// ----------------------------------------------------------------------------

void Engine::render(const RenderCallback_t render, uint8_t maxDisplayedMenuItems) const {    
  static uint8_t laststart =0;
  if (!currentItem || currentItem == &Menu::NullItem) {
    return;
  }

  uint8_t start = laststart;
  uint8_t itemCount = 0;
  Info_t mi = getItemInfo(currentItem);

  //beginning of the window
  if(start > mi.position-1) {
    start = mi.position == 0 ? 0 : mi.position - 1;
  }
  
  if((start + maxDisplayedMenuItems) < mi.position + 2) {
    start = mi.position + 2 - maxDisplayedMenuItems;
  }
  
  if((start + maxDisplayedMenuItems) > mi.siblings){
    start = mi.siblings>maxDisplayedMenuItems ? mi.siblings-maxDisplayedMenuItems : 0;
  }
  
  laststart= start; 
  
  // first item in current menu level
  const Item_t * i = getChild(getParent());  
  for (; i && i != & Menu::NullItem; i = getNext(i)) {
    if (itemCount - start >= maxDisplayedMenuItems) break;
    if (itemCount >= start) render(i, itemCount - start);
    itemCount++;
  }
}

// ----------------------------------------------------------------------------

}; // end namespace

// ----------------------------------------------------------------------------