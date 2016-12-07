sleep 5
sudo ip route add 172.16.2.128/28 via 172.16.2.1 #LAN1
sleep 2
sudo ip route add 172.16.2.144/28 via 172.16.2.1 #LAN3
