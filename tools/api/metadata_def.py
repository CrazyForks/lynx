# Copyright 2025 The Lynx Authors. All rights reserved.
# Licensed under the Apache License Version 2.0 that can be found in the
# LICENSE file in the root directory of this source tree.

# /usr/bin/env python3
# -*- coding: utf-8 -*-

from dataclasses import dataclass


@dataclass
class BaseMemberType:
    MethodType = "method"
    PropertyType = "property"
    VariableType = "variable"
    TypedefType = "typedef"
    EnumType = "enum"
    DefineType = "define"
    UnknownType = "unknown"


@dataclass
class BaseMember:
    name: str
    type: BaseMemberType
    brief_desc: str
    detailed_desc: str
    definition: str

    def get_member_dump_str(self) -> str:
        spaces = f'{"  " if self.type != BaseMemberType.EnumType else ""}'
        return f"{spaces}{self.definition}"


@dataclass
class BaseObjectType:
    ClassType = "class"
    InterfaceType = "interface"
    EnumType = "enum"
    FileType = "file"
    StructType = "struct"
    CategoryType = "category"
    ProtocolType = "protocol"
    UnknownType = "unknown"


@dataclass
class BaseObject:
    name: str
    type: BaseObjectType
    brief_desc: str
    detailed_desc: str
    definition: str
    children: list[BaseMember]

    def get_api_str(self) -> str:
        api_str: str = f"{self.definition} {{\n" if self.definition else ""
        for member in self.children:
            member_definition = member.get_member_dump_str()
            if member_definition:
                api_str += f"{member_definition}\n"
        if self.definition:
            api_str += "}\n\n"
        elif api_str:
            api_str += "\n"
        return api_str
