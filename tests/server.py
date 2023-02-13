import psi_oprf as psi
import logging
import datetime

port = 1213
logging.basicConfig(filename='./example.log', level= logging.INFO)
timestamp = datetime.datetime.now().strftime('%Y%m%d-%H%M%S-%f')
input_path = f'/app/data/server-input-20230130-063045-155318-{timestamp}'
logging.info(input_path)
psi.PsiRun(1024, 1024, 10, 9, "127.0.0.1", 1)

