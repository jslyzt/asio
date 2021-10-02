-- plat
set_config("plat", os.host())

-- project
set_project("asio")

-- set xmake minimum version
set_xmakever("2.3.1")

-- set common flags
set_languages("c++17")
set_warnings("all")     -- -Wall
set_symbols("debug")    -- dbg symbols


-- 编译参数
if is_plat("windows") then
    add_cxflags("-DWIN32 -D_WIN32 -D_CRT_SECURE_NO_WARNINGS -D_WIN32_WINNT=0x0601")
    if is_mode("debug") then
        set_optimize("none")
        set_runtimes("MDd")
    else
        set_optimize("fastest")
        set_runtimes("MD")
    end
else
    set_optimize("faster")   -- faster: -O2  fastest: -O3  none: -O0
    add_cxflags("-fPIC -std=c++17 -Wno-deprecated -fno-strict-aliasing -Wno-overloaded-virtual")
    if is_mode("debug") then
        add_cxflags("-Wall -g")
    else
        add_cxflags("-O2 -Wall -fno-strict-aliasing")
    end
end


-- include dir
add_includedirs(
    "include"
)

-- include sub-projects
includes("src")
