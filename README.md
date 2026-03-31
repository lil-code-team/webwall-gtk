# 🎨 WebWall GTK - Interactive Wallpaper

A modern and lightweight interactive wallpaper application for Linux, built with GTK 3 and WebKit2. Create and customize dynamic wallpapers using HTML, CSS, and JavaScript.

![License: MIT](https://img.shields.io/badge/license-MIT-blue)
![Language: C](https://img.shields.io/badge/language-C-blue)
![Platform: Linux](https://img.shields.io/badge/platform-Linux-green)

## ✨ Features

- 🎯 **Full HTML5 Rendering** - Uses WebKit2 to render any web content as wallpaper
- 🖥️ **Layer Shell Integration** - Compatible with Wayland and X11 via gtk-layer-shell
- 🌐 **Link Navigation** - Clicks on links open in the default browser
- ⚙️ **Fully Customizable** - Customize via HTML/CSS/JS in `~/.config/wallpaper/index.html`
- 🔧 **Lightweight and Fast** - Written in C with minimal dependencies
- 📦 **Automatic Build** - GitHub Actions for compilation and releases

## 🚀 Quick Start

### Dependencies

#### Ubuntu/Debian

```bash
sudo apt-get install -y \
  build-essential \
  libgtk-3-dev \
  libgtk-layer-shell-dev \
  libwebkit2gtk-4.0-dev \
  pkg-config
```

#### Fedora/RHEL

```bash
sudo dnf install -y \
  gcc \
  gtk3-devel \
  gtk-layer-shell-devel \
  webkit2gtk3-devel \
  pkg-config
```

#### Arch

```bash
sudo pacman -S base-devel gtk3 gtk-layer-shell webkit2gtk
```

### Build

```bash
# Clone or enter the repository
git clone https://github.com/lil-code-team/webwall-gtk.git
cd webwall-gtk

# Compile
gcc wallpaper.c -o ./build/webwall-gtk `pkg-config --cflags --libs gtk+-3.0 gtk-layer-shell-0 webkit2gtk-4.0`

# Run
./build/webwall-gtk
```

## 📖 How to Use

### Installing the Executable

```bash
# Copy to an accessible location
sudo cp webwall-gtk /usr/local/bin/

# Or for personal use
mkdir -p ~/.local/bin
cp webwall-gtk ~/.local/bin/
```

### Configuration

The default configuration file is loaded from: `~/.config/wallpaper/index.html`

1. **Create the configuration directory (if it doesn't exist):**

   ```bash
   mkdir -p ~/.config/wallpaper
   ```

2. **Copy the example file or create a new one:**

   ```bash
   cp index.example.html ~/.config/wallpaper/index.html
   ```

3. **Edit the `~/.config/wallpaper/index.html` file as desired.**

### Configuration Examples

#### Simple Wallpaper with Gradient

```html
<!DOCTYPE html>
<html>
  <head>
    <style>
      body {
        margin: 0;
        height: 100vh;
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      }
    </style>
  </head>
  <body></body>
</html>
```

#### Wallpaper with Clock

```html
<!DOCTYPE html>
<html>
  <head>
    <style>
      body {
        margin: 0;
        height: 100vh;
        display: flex;
        align-items: center;
        justify-content: center;
        background: #0a0e27;
        color: #fff;
        font-family: monospace;
        font-size: 48px;
      }
    </style>
  </head>
  <body>
    <div id="clock"></div>
    <script>
      setInterval(() => {
        document.getElementById("clock").textContent =
          new Date().toLocaleTimeString();
      }, 1000);
    </script>
  </body>
</html>
```

#### Wallpaper with Background Image

```html
<!DOCTYPE html>
<html>
  <head>
    <style>
      body {
        margin: 0;
        height: 100vh;
        background-image: url("file:///path/to/image.jpg");
        background-size: cover;
        background-position: center;
      }
    </style>
  </head>
  <body></body>
</html>
```

### Auto-start

#### Systemd User Service

Create `~/.config/systemd/user/webwall-gtk.service`:

```ini
[Unit]
Description=WebWall GTK Wallpaper
After=graphical-session-started.target
PartOf=graphical-session.target

[Service]
Type=simple
ExecStart=%h/.local/bin/webwall-gtk
Restart=on-failure

[Install]
WantedBy=graphical-session.target
```

Enable with:

```bash
systemctl --user enable webwall-gtk
systemctl --user start webwall-gtk
```

#### Desktop Entry

Create `~/.config/autostart/webwall-gtk.desktop`:

```ini
[Desktop Entry]
Type=Application
Name=WebWall GTK
Comment=Interactive HTML Wallpaper
Exec=/usr/local/bin/webwall-gtk
Hidden=false
NoDisplay=false
X-GNOME-Autostart-enabled=true
```

## 🏗️ Project Structure

```
.
├── wallpaper.c              # Main source code
├── webwall-gtk              # Compiled executable
├── index.html               # Wallpaper configuration (active)
├── index.example.html       # Configuration example
├── README.md                # This file
├── .github/
│   └── workflows/           # GitHub Actions
│       ├── build-and-release.yml
│       └── validate.yml
└── .gitignore               # Git ignore file
```

## 🔧 Development

### Debug Build

```bash
gcc -g wallpaper.c -o wallpaper `pkg-config --cflags --libs gtk+-3.0 gtk-layer-shell-0 webkit2gtk-4.0`
```

### Local Testing

```bash
# Test with example configuration
cp index.example.html ~/.config/wallpaper/index.html

# Run
./wallpaper
```

### Automatic Build

This project uses GitHub Actions for:

- ✅ Validating compilation on every push/PR
- 📦 Creating automatic releases for the `main` branch
- 🏷️ Generating Semver versions (v1.0.0, v1.0.1, etc)

See [`.github/WORKFLOWS.md`](.github/WORKFLOWS.md) for more details.

## 📦 Releases

Releases include:

- `wallpaper` - Compiled executable
- `index.html` - Default configuration
- `index.example.html` - Configuration example
- `wallpaper-src-*.tar.gz` - Complete source code

Download from: https://github.com/lil-code-team/webwall-gtk/releases

## ⚙️ Environment Variables

- `HOME` - Used to locate `~/.config/wallpaper/index.html`

Example:

```bash
HOME=/home/username ./wallpaper
```

## 🐛 Troubleshooting

### Wallpaper not showing

- Make sure the `index.html` file exists in `~/.config/wallpaper/`
- Test with a simple HTML file
- Check logs: `journalctl --user -u wallpaper -f` (if using systemd)

### Compilation error

```bash
# Check if dependencies are installed
pkg-config --cflags gtk+-3.0 gtk-layer-shell-0 webkit2gtk-4.0

# Test each library individually
pkg-config --modversion gtk+-3.0
pkg-config --modversion webkit2gtk-4.0
```

### Poor performance

- Minimize complex CSS animations
- Use `will-change` selectively
- Consider using compressed images

## 📄 License

This project is licensed under the MIT License. See the LICENSE file for details.

## 🤝 Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a branch for your feature (`git checkout -b feature/MyFeature`)
3. Commit your changes (`git commit -am 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/MyFeature`)
5. Open a Pull Request

### Development Guidelines

- Keep C code clean and readable
- Add comments for complex logic
- Test on both Wayland and X11 before submitting
- Follow the existing code style

## 👥 Authors

Developed by **lil-code-team**

## 📞 Support

- 🐛 [Issues](https://github.com/lil-code-team/webwall-gtk/issues)
- 💬 [Discussions](https://github.com/lil-code-team/webwall-gtk/discussions)

## 🔗 Useful Links

- [GTK 3 Documentation](https://developer.gnome.org/gtk3/stable/)
- [gtk-layer-shell](https://github.com/wmww/gtk-layer-shell)
- [WebKit2 GTK](https://webkitgtk.org/)
- [Wayland Protocol](https://wayland.freedesktop.org/)

---

Made with ❤️ by lil-code-team
