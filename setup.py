from setuptools import setup, Extension
from age_cda import VERSION

with open("README.md", "r", encoding='utf8') as fh:
    long_description = fh.read()

setup(
    name             = 'age_cda',
    version          = VERSION.VERSION,
    description      = 'Detection of Community by maximizing modularity',
    long_description=long_description,
    long_description_content_type="text/markdown",
    author           = 'Moontasir Mahmood',
    author_email     = 'moontasir042@gmail.com',
    url              = 'https://github.com/Munmud/Community-Detection-Modularity',
    license          = 'Apache2.0',
    install_requires = [],
    packages         = ['age_cda'],
    package_data={'age_cda': ['lib_ubuntu/*.so', 'lib_windows/x64/Release/*.dll', 'lib_windows/x86/Release/*.dll']},
    keywords         = ['Community-Detection', 'Modularity', 'Reichardt and Bornholdt','Newman', 'partition network', 'k means cluster'],
    python_requires  = '>=3.9',
    classifiers      = [
        'Programming Language :: Python :: 3.9'
    ]
)