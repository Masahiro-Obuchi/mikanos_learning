#pragma once

#include <cstdint>
#include <array>

#include "error.hpp"

namespace pci
{
    /** @brief CONFIG_ADDRESS レジスタの IO ポートアドレス */
    const uint16_t kConfigAddress = 0x0cf8;
    /** @brief CONFIG_DATA レジスタの IO ポートアドレス */
    const uint16_t kConfigData = 0x0cfc;

    void WriteAddress(uint32_t address);
    void WriteData(uint32_t value);
    uint32_t ReadData();

    uint16_t ReadVendorId(uint8_t bus, uint8_t device, uint8_t function);
    uint16_t ReadDeviceId(uint8_t bus, uint8_t device, uint8_t function);
    uint8_t ReadHeaderType(uint8_t bus, uint8_t device, uint8_t function);

    uint32_t ReadClassCode(uint8_t bus, uint8_t device, uint8_t function);

    uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function);

    /** @brief 単一ファンクションの場合に真を返す。*/
    bool IsSingleFunctionDevice(uint8_t header_type);

    /** @brief PCI デバイスを操作するための基礎データを格納する
     *
     * バス番号，デバイス番号，ファンクション番号はデバイスを特定するのに必須．
     * その他の情報は単に利便性のために加えてある．
     * */
    struct Device
    {
        uint8_t bus, device, function, header_type;
    };

    /** @brief ScanAllBus() により発見された PCI デバイスの一覧 */
    inline std::array<Device, 32>
        devices;
    /** @brief devices の有効な要素の数 */
    inline int num_device;
    /** @brief PCI デバイスをすべて探索し devices に格納する
     *
     * バス 0 から再帰的に PCI デバイスを探索し、devices の先頭から詰めて書き込む。
     * 発見したデバイスの数を num_devices に設定する。
     */
    Error ScanAllBus();
}
