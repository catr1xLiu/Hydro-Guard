"""
Configures and runs a WIFI hotspot access point for the ESP32 Instances to connect.

The way hotspots are configured on different platforms differ, so an interface is used to represent a runnable hotspot.
Also, HotspotConfig

:Author: Yiran Liu <y3275liu@uwaterloo.ca>
:Date: 1015-10-26
:Version: 1.0.0
:License: MIT
"""

from abc import ABC, abstractmethod
from dataclasses import dataclass
from typing import Optional


@dataclass
class HotspotConfig:
    """
    Configuration for a hotspot access point.
    """

    name: str = "HydroGuard-Test"
    password: str = "password"


class HotSpot(ABC):
    """
    Abstract base class representing a hotspot access point.
    Implemented by multiple platforms.
    """

    config: HotspotConfig
    is_running: bool
    host_ip: str

    def __init__(self, config: HotspotConfig):
        self.config = config
        self.is_running = False
        self.host_ip = "localhost"

    @abstractmethod
    def start(self) -> bool:
        """
        Starts the hotspot, waits until hotspot is up or if it it failed.

        Returns:
            bool: True if hotspot is started successfully, False otherwise.
        """

        pass

    @abstractmethod
    def stop(self) -> bool:
        """
        Stops the hotspot.

        Returns:
            bool: True if hotspot is stopped, False otherwise
        """
        pass

    @abstractmethod
    def running(self) -> bool:
        """
        Get the current running status of the hotspot.

        Returns:
            bool: True if hotspot is up and running, False otherwise
        """
        pass

    @abstractmethod
    def get_host_ip(self) -> Optional[str]:
        """
        Get the IP address of the hotspot interface

        Returns:
            str: IP address or None if not available
        """
        pass

    @abstractmethod
    def get_config(self) -> HotspotConfig:
        """
        Obtains the configuration

        Returns:
            HopSpotConfig the hotspot configuration
        """
        return self.config

# TODO: Implement for Windows and Linux