# utf-8
export LC_ALL=en_US.UTF-8

# display
xrandr --output HDMI-0 --mode 1920x1080 --rate 60

# setup nvidia
nvidia-settings --assign CurrentMetaMode="HDMI-0:nvidia-auto-select +0+0 { ForceCompositionPipeline = On }"

# compositor
picom --config ~/.config/picom.conf &

# colors and xterm setup
xrdb -load ~/.Xresources &

# keyboard layout
setxkbmap -layout us

#make the cursor fast af
xset r rate 300 50

# fix pointer shape
xsetroot -cursor_name left_ptr &

# well behaved mouse curosr
unclutter -grab &
#unclutter -root -visible &

# fonts
xset +fp /usr/local/share/fonts/urwfonts &
xset +fp /usr/local/share/fonts/terminus-font &
xset +fp /usr/local/share/fonts/webfonts &
xset +fp /usr/local/share/fonts/spleen/ &
xset +fp ~/.fonts &
xset fp rehash &

# wm
exec ck-launch-session i3

