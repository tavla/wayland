man_conf = configuration_data()
man_conf.set('version', meson.project_version())

configure_file(
	input: 'wayland-scanner.man',
	output: 'wayland-scanner.1',
	install_dir: join_paths(dir_man, 'man1'),
	configuration: man_conf
)
