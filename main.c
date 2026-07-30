#include <stdio.h>
#include <search.h>
#include <nvml.h>

typedef struct {
	unsigned int max;
	unsigned int targetSpeed;
} tempConf;

int main() {
	nvmlReturn_t result;
	nvmlDevice_t device;
	unsigned int temp = 0;

	result = nvmlInit();
	if (NVML_SUCCESS != result) {
		printf("Failed to initialize NVML: %s\n", nvmlErrorString(result));
		return 1;
	}

	result = nvmlDeviceGetHandleByIndex(0, &device);
	if (NVML_SUCCESS != result) {
		printf("Failed to get handle for device 0: %s\n", nvmlErrorString(result));
		nvmlShutdown();
		return 1;
	}

	result = nvmlDeviceSetFanControlPolicy(device, 0, NVML_FAN_POLICY_MANUAL);
	if (NVML_SUCCESS != result) {
		printf("Failed to set fan policy to manual: %s\n", nvmlErrorString(result));
		nvmlShutdown();
		return 1;
	}else {
		printf("Fan policy successfully changed to manual");
	}

	tempConf config[] = {
		{35, 50},
		{50, 70},
		{70, 85},
		{2000, 100}
	};
	int size = sizeof(config) / sizeof(config[0]);

	while (1) {
		result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
		if (NVML_SUCCESS != result) {
			printf("failed to get GPU temp: %s\n", nvmlErrorString(result));
			continue;
		}
		
		int i = 0;
		while (temp > config[i].max) i++;

		result = nvmlDeviceSetFanSpeed_v2(device, 0, config[i].targetSpeed);
		if (NVML_SUCCESS != result) {
			printf("Failed to set fan speed: %s\n", nvmlErrorString(result));
		}else {
			printf("GPU temp (%d), set fan speed to: %d\n", temp, config[i].targetSpeed);
		}
	}

	return 0;
}
