# -*- coding: utf-8 -*-
"""
Created on Sat Dec 31 07:46:11 2016

@author: achmadi
"""

import numpy as np
from scipy import stats as st
import pandas as pd
import matplotlib.pyplot as plt
import statsmodels.api as sm

from data_load import DataLoad

dat = DataLoad()
#dat.plot()

d = {'u11':dat.u11, 'u12':dat.u12, 'u13':dat.u13}
df = pd.DataFrame(data=d)