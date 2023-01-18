# Register the standard build
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/ESP32Controller.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ESP32Controller.fpp"
)
register_fprime_module()
