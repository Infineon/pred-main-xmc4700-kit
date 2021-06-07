
start-full:
	@echo "=== Start installing dependencies ==="
	@./start.sh

deploy-full:
	@echo "=== Deploy stack to AWS ==="
	@./tools/bash/env.sh && ./tools/bash/deploy-stack.sh

start:
	@echo "=== Start installing dependencies ==="
	@./start.sh

deploy:
	@echo "=== Deploy stack to AWS ==="
	@./tools/bash/env.sh && ./tools/bash/deploy-stack-cf.sh

describe-stack:
	@echo "=== Describe deployed stack ==="
	@./tools/bash/env.sh && ./tools/bash/describe-stack.sh

configure:
	@echo "=== Enter AWS CLI credentials ==="
	@aws configure

register-device:
	@echo "=== Register device in IoT and Kibana ==="
	@ ./tools/bash/env.sh && python3 ./tools/pyscripts/create_thing.py

register-device-in-kibana:
	@echo "=== Register device in Kibana ==="
	@ ./tools/bash/env.sh && python3 ./tools/pyscripts/kibana_register.py

deregister-device:
	@./tools/bash/env.sh && python3 ./tools/pyscripts/delete_thing.py

delete-stack:
	@echo "=== Delete stack from AWS ==="
	@./tools/bash/env.sh && aws cloudformation delete-stack --stack-name InfineonKitRealtime && aws cloudformation wait stack-delete-complete --stack-name InfineonKitRealtime
