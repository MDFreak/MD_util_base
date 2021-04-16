/*************************************************************************
|  Filename..............: linked_list.hpp
 * Project...............: part of standard utilities
 * Autor.................: Martin Dorfner (MD)
 * Date .................: 20.11.2020
 *-----------------------------------------------------------------------
 * Function:
 *   provide linked list support with small footprint
 *-----------------------------------------------------------------------
 * Dependecies:
 *   md_defines.h    (utility intern)
 *   linked_list.cpp implementation
 *-----------------------------------------------------------------------
 * Description:
 *   Primitives for handling linked lists
 *   - only void-pointers are connected with attributes
 *   - no extra memory allocation is done
 *   - some cell types are handled from derived classes like sorted list
 *     => type has to be defined and implemented
 *   - derivatives with specified types have to be introduced as well
 *   goal is small footprint with high performance
 ************************************************************************
 * Version| Date   | Changes                                    | Autor
 *-----------------------------------------------------------------------
 * 0.1.0  |20.11.20| import from former project                 | MD
*-----------------------------------------------------------------------*/

#ifndef _LINKED_LIST_HPP_
  #define _LINKED_LIST_HPP_

  #include <stdlib.h>
  #include <Arduino.h>
  #include <md_defines.h>

  #define DICT_MAX_NAME_LEN 14
  #define MD_CELL_TYPE_INT8  0
  #define MD_CELL_TYPE_INT16 0

  #define OFIRST   FALSE      // function call
  #define OLAST    TRUE
  #define OMAX     0x7FFF // = int16 max

  #define MD_DEBUG          TRUE
  #define DICT_DEBUG        TRUE

  // --- base classes md_cell, md_list
    class md_cell           /* Abstrakte Basisklasse fuer Listenelemente */
      {
        protected:
          void*     _pNext  = NULL;   // Pointer auf naechstes Listenelement
          void*     _pPriv  = NULL;
          dattype_t _tCell  = T_UNDEF;

        public:
          md_cell()                    { init(); }
          md_cell(dattype_t celltype)  { init(); _tCell = celltype; }
          ~md_cell() {}

          void*     pNext()    { return (void*) _pNext; }
          void*     pPriv()    { return (void*) _pPriv;}
          dattype_t celltype() { return _tCell; }
          void      setNext    (void* pNext) { _pNext = pNext; }
          void      setPriv    (void* pPriv) { _pPriv = pPriv; }
          void      setCelltype(dattype_t celltype) { _tCell = celltype; }
        private:
          void      init() { _pNext = _pPriv  = NULL; _tCell = T_UNDEF; }
      };
    //
    class md_list
      {
        private:
          md_cell* _pFirst = NULL;
          md_cell* _pLast  = NULL;
          uint16_t _count  = 0;

        public:
          md_list()  { _pFirst = _pLast = NULL; _count = 0; } // Konstruktor
          ~md_list() {}

          uint16_t count () { return _count; }
          void*    pFirst() { return (void*) _pFirst; }
          void*    pLast () { return (void*) _pLast; }
          uint16_t add   (void* pCell);
          uint16_t rem   (bool  first = OFIRST);
      };

    #endif
