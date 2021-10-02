target("asio")
    set_kind("binary")
    add_files("*.cpp")
    set_targetdir("../bin")
    if is_plat("windows") and is_mode("debug") then
        set_basename("asio_d")
    end