from dataclasses import dataclass
from pathlib import Path
from typing import Optional, Dict, List
import yaml
import os

from src.utils.logger import Logger

PROJECT_ROOT = Path(__file__).parent.parent.parent
CONFIG_DIR = PROJECT_ROOT / "config"
CONFIG_FILE = CONFIG_DIR / "config.yaml"

@dataclass
class ConnectionConfig:
    port: str
    baudrate: int
    timeout: float = 2.0


@dataclass
class InputConfig:
    label: str
    button_id: Optional[int] = None
    axis_id: Optional[int] = None

@dataclass()
class OutputConfig:
    arduino_ids: List[int]
    label: str
    custom: bool


@dataclass
class AppConfig:
    connection: ConnectionConfig
    inputs: Dict[int, InputConfig]
    simvars: List[str]
    outputs: Dict[str, OutputConfig] # Mapeo: Nombre SimVar -> ID Arduino


class ConfigLoader:
    _logger = Logger("ConfigLoader")

    @staticmethod
    def load(config_path: str) -> AppConfig:
        ConfigLoader._logger.info(f"Cargando configuración desde {config_path}...")

        if not os.path.exists(config_path):
            error_msg = f"El archivo de configuración no se encontró: {config_path}"
            ConfigLoader._logger.error(error_msg)
            raise FileNotFoundError(error_msg)

        try:
            with open(config_path, 'r') as file:
                raw_data = yaml.safe_load(file) or {}
        except yaml.YAMLError as e:
            error_msg = f"YAML mal escrito: {e}"
            ConfigLoader._logger.error(error_msg)
            raise ValueError(error_msg)

        conn_data = raw_data.get('connection', {})
        connection = ConnectionConfig(
            port=conn_data.get('port', '/dev/ttyUSB0'),
            baudrate=conn_data.get('baudrate', 9600)
        )

        raw_inputs = raw_data.get('inputs', {})
        inputs = {}

        for input_id, props in raw_inputs.items():
            inputs[input_id] = InputConfig(
                label=props.get('label', f'INPUT_{input_id}'),
                button_id=props.get('button_id'),
                axis_id=props.get('axis_id')
            )


        outputs = raw_data.get('simvars', {})
        simvars = []

        for name, props in outputs.items():
            outputs[name] = OutputConfig(
                arduino_ids=props.get('arduino_ids'),
                label=props.get('label', name),
                custom=props.get('custom', False)
            )
            if not outputs[name].custom:
                simvars.append(name)

        ConfigLoader._logger.info("Configuración cargada exitosamente.")

        return AppConfig(
            connection=connection,
            inputs=inputs,
            simvars=simvars,
            outputs=outputs
        )