1. Adjust script to your needs
2. Copy to watch
3. Make executable

```bash
ssh ceres@192.168.2.15 'mkdir ~/script-shell'
scp script-name.sh ceres@192.168.2.15:~/script-shell
ssh ceres@192.168.2.15 'chmod 700 ~/script-shell/script-name.sh'
```
