#######################################
# Effect

set(mousemark_SOURCES
    main.cpp
    mousemark.cpp
)

kconfig_add_kcfg_files(mousemark_SOURCES
    mousemarkconfig.kcfgc
)

kwin4_add_effect_module(kwin4_effect_mousemark ${mousemark_SOURCES})

#######################################
# Config
set(kwin_mousemark_config_SRCS mousemark_config.cpp)
ki18n_wrap_ui(kwin_mousemark_config_SRCS mousemark_config.ui)
kconfig_add_kcfg_files(kwin_mousemark_config_SRCS mousemarkconfig.kcfgc)

kwin_add_effect_config(kwin_mousemark_config ${kwin_mousemark_config_SRCS})

target_link_libraries(kwin_mousemark_config
    KF5::ConfigWidgets
    KF5::GlobalAccel
    KF5::I18n
    KF5::TextWidgets
    KF5::XmlGui
    KWinEffectsInterface
)
