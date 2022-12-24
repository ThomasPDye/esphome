"""Tests for the rpr0521 component"""


def test_rpr0521_device_class_set(generate_main):
    main_cpp = generate_main("test/component_tests/sensor/rpr0521/test_rpr0521.yaml")
    assert 's_1->set_device_class("distance");' in main_cpp
